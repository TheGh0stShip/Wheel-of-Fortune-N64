# Wheel of Fortune (Nintendo 64)

Matching decompilation for the USA release. This import contains C recovered with N64 Decomp Kit, Round 12 (lab commit `9ed9048`). An independent rebuild and verification replay passed for every published C match.

| Metric | Verified | Catalogued | Progress |
|---|---:|---:|---:|
| Matching C code bytes | 396,752 | 402,772 | 98.50% |
| Matching C functions | 750 | 775 | 96.77% |
| Matching C bytes in the verified pinned link | 396,752 | 402,772 | 98.50% |
| Verified source of any kind | 775 | 775 | 100.00% |

These measurements cover the corrected catalogue of executable function intervals. All 750 verified C functions and all remaining assembly/runtime units link from source; the resulting cartridge matches the USA ROM byte for byte. The project is therefore 100% source-accounted. The matching-C ceiling is 98.50% under the repository's rule because architecture-specific assembly and GCC's inline-assembly division runtime cannot honestly receive ordinary-C credit. See the [link verification record](docs/pinned-link.md) and the [machine-readable report](decomphub.progress.json).

[ByteMatch](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64) receives the same scoped figures under the `usa-catalogued` version.

[![Matching C bytes in the catalogue](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64.svg?version=usa-catalogued&category=catalogued-code&measure=matched_code_percent&label=Catalogued%20C%20bytes)](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64/usa-catalogued)

ByteMatch's fuzzy score is a lower bound based on exact matches. Partial similarity is unmeasured. Its fully linked figure counts only verified C bytes linked into the mixed image.

- ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`
- ROM size 4,194,304 bytes
- `src/main/` contains the verified function sources.
- `MATCHED.tsv` records image, address, owned code size, and recipe for each source.
- `source-accounted.tsv` covers all 775 catalogued functions with immutable source hashes.
- `asm/accounted/` contains the exact assembly/runtime sources for ranges that cannot be ordinary C.
- `donor` rows retain provenance for library C independently sourced from other public N64 decompilations; every such row was rebuilt against this ROM before receiving credit. See [source provenance](docs/source-provenance.md).

Supply your own USA ROM and the applicable compiler tools to reproduce a match. This repository contains C sources and verification metadata.

With N64 Decomp Kit, initialize a local project, then check a function using its row in `MATCHED.tsv`:

```sh
n64dk decompile-init 'Wheel of Fortune (USA).z64' --out local-project
n64dk match --project local-project --image-name main --no-infer \
  --addr 0x80002348 --size 0x250 --pipeline kmc+asn64 \
  --flags="-O0 -G0 -mips3 -mgp32 -mfp32" \
  --symbols survey/symbol_addrs.txt --symbols survey/sdk_symbols.txt \
  src/main/func_80002348.c
```
