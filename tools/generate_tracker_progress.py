"""Generate a scoped DecompHub report from a reviewed function inventory."""

import argparse
import csv
import hashlib
import json
import re
from collections import defaultdict
from pathlib import Path


def inventory(path):
    with path.open(encoding="utf-8", newline="") as stream:
        return list(csv.DictReader(stream, delimiter="\t", strict=True))


def function_key(row):
    return row["image"], int(row["vram"], 0)


def linked_functions(root, rows):
    """Read a reviewed mixed-image link result tied to the published sources."""
    path = root / "progress-linked.tsv"
    if not path.exists():
        return set()
    strict = {
        function_key(row): row for row in rows
        if row["outcome"] == "exact" and row["reproduced_by"] == "C"
    }
    linked = set()
    for entry in inventory(path):
        key = function_key(entry)
        original = strict.get(key)
        if key in linked or original is None:
            raise ValueError(f"stale or invalid linked unit: {key}")
        if (int(entry["code_size"], 0) != int(original["code_size"], 0)
                or entry["function"] != original["function"]
                or entry["source_sha256"] != original["source_sha256"]):
            raise ValueError(f"stale or invalid linked unit: {key}")
        linked.add(key)
    return linked


def generate(root):
    config = json.loads((root / "progress-config.json").read_text(encoding="utf-8"))
    rows = inventory(root / "progress-inventory.tsv")
    matched = inventory(root / "MATCHED.tsv")
    matches = {function_key(row): row for row in matched}
    if not rows or len(matched) != len(matches):
        raise ValueError("empty inventory or duplicate match")

    ranges = defaultdict(list)
    files = set()
    verified = set()
    total_bytes = matching_bytes = 0
    for row in rows:
        image, address = key = function_key(row)
        size = int(row["code_size"], 0)
        if address < 0 or size <= 0:
            raise ValueError(f"invalid range: {key}")
        ranges[image].append((address, address + size))
        total_bytes += size
        if row["outcome"] != "exact" or row["reproduced_by"] != "C":
            continue
        published = matches.get(key)
        if published is None or any(
            published[field] != row[field]
            for field in ("function", "code_size", "outcome", "reproduced_by", "source")
        ):
            raise ValueError(f"strict match disagrees with inventory: {key}")
        source = Path(row["source"])
        if source.parts[:1] != ("src",) or ".." in source.parts or source.suffix != ".c" or source in files:
            raise ValueError(f"invalid or duplicate C source: {source}")
        path = root / source
        if path.resolve().relative_to(root.resolve()) != source:
            raise ValueError(f"source path redirects: {source}")
        data = path.read_bytes()
        if hashlib.sha256(data).hexdigest() != row["source_sha256"]:
            raise ValueError(f"verified source digest changed: {source}")
        if re.search(rb'\b(?:asm|__asm|__asm__|GLOBAL_ASM|INCLUDE_ASM)\s*\(', data):
            raise ValueError(f"assembly-assisted source needs a separate disposition: {source}")
        verified.add(key)
        files.add(source)
        matching_bytes += size
    for image, intervals in ranges.items():
        intervals.sort()
        if any(end > start for (_, end), (start, _) in zip(intervals, intervals[1:])):
            raise ValueError(f"overlapping code intervals: {image}")
    if verified != set(matches) or files != {p.relative_to(root) for p in (root / "src").rglob("*.c")}:
        raise ValueError("published C sources and strict matches differ")

    def track(track_id, label, completed, total, unit):
        return {
            "id": track_id, "label": label, "scope": config["scope"],
            "measurement": {"kind": "ratio", "completed": completed, "total": total, "unit": unit},
        }

    tracks = [
        track("matching-code", "Matching decompiled C code", matching_bytes, total_bytes, "bytes"),
        track("matching-functions", "C-decompiled function candidates", len(verified), len(rows), "functions"),
    ]
    if (root / "progress-linked.tsv").is_file():
        linked = linked_functions(root, rows)
        linked_bytes = sum(int(row["code_size"], 0) for row in rows if function_key(row) in linked)
        tracks.append(track("linked-c-code", "Matching C linked in a verified pinned image",
                            linked_bytes, total_bytes, "bytes"))
    return {
        "format": "decomphub.progress/v1",
        "repository": config["repository"],
        "tracks": tracks,
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--objdiff", type=Path, help="also write an objdiff v2 report for ByteMatch")
    args = parser.parse_args()
    output = args.root / "decomphub.progress.json"
    progress = generate(args.root)
    report = json.dumps(progress, indent=2) + "\n"
    if args.check:
        if output.read_text(encoding="utf-8") != report:
            parser.exit(1, "decomphub.progress.json is stale\n")
    else:
        output.write_text(report, encoding="utf-8")
    if args.objdiff:
        args.objdiff.parent.mkdir(parents=True, exist_ok=True)
        rows = inventory(args.root / "progress-inventory.tsv")
        objdiff = objdiff_report(progress, rows, linked_functions(args.root, rows))
        args.objdiff.write_text(json.dumps(objdiff, indent=2) + "\n", encoding="utf-8")


def objdiff_report(progress, rows, linked=()):
    code, functions = (track["measurement"] for track in progress["tracks"][:2])
    category = "catalogued-code"

    def measures(size, matching, count, matched, linked_bytes, linked_count):
        exact_percent = 100 * matching / size
        return {
            "total_code": str(size), "matched_code": str(matching),
            "matched_code_percent": exact_percent,
            # Exact matches contribute at full weight. Unmeasured partial
            # matches receive no credit, so this is a lower bound.
            "fuzzy_match_percent": exact_percent,
            "total_functions": count, "matched_functions": matched,
            "matched_functions_percent": 100 * matched / count,
            "total_units": count,
            "complete_code": str(linked_bytes),
            "complete_code_percent": 100 * linked_bytes / size,
            "complete_units": linked_count,
        }

    units = []
    linked_bytes = 0
    for row in rows:
        size = int(row["code_size"], 0)
        matched = row["outcome"] == "exact" and row["reproduced_by"] == "C"
        address = str(int(row["vram"], 0))
        complete = function_key(row) in linked
        if complete:
            linked_bytes += size
        metadata = {"progress_categories": [category]}
        if complete:
            metadata["complete"] = True
        if matched:
            metadata["source_path"] = row["source"]
        units.append({
            "name": f"{row['image']}/{row['function']}@{row['vram']}",
            "measures": measures(size, size if matched else 0, 1, int(matched),
                                 size if complete else 0, int(complete)),
            "functions": [{
                "name": row["function"], "size": str(size), "address": address,
                "fuzzy_match_percent": 100.0 if matched else 0.0,
                "metadata": {"virtual_address": address},
            }],
            "metadata": metadata,
        })
    totals = measures(code["total"], code["completed"], functions["total"], functions["completed"],
                      linked_bytes, len(linked))
    return {
        "version": 2, "measures": totals, "units": units,
        "categories": [{"id": category, "name": "Catalogued code only", "measures": totals}],
    }


if __name__ == "__main__":
    main()
