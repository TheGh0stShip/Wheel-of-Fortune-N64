#!/usr/bin/env python3
"""Reject compatibility shims that can hide incomplete m2c translations."""

from __future__ import annotations

from pathlib import Path


FORBIDDEN = (
    "N64DK_M2C_PRELUDE",
    "M2C_ERROR",
    "M2C_TRAP_IF",
    "M2C_BREAK",
    "M2C_CARRY",
    "M2C_LWL",
    "M2C_FIRST3BYTES",
    "M2C_UNALIGNED32",
    "M2C_BITWISE",
    "m2c_unhandled",
)


def main() -> int:
    failures: list[str] = []
    sources = sorted(Path("src/main").glob("*.c"))
    for source in sources:
        text = source.read_text(encoding="utf-8")
        for token in FORBIDDEN:
            if token in text:
                failures.append(f"{source}: forbidden incomplete-lift token {token}")
    if failures:
        print("\n".join(failures))
        return 1
    print(f"source-quality check passed for {len(sources)} C files")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
