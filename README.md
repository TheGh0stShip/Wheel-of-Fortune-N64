# Wheel of Fortune (Nintendo 64)

Matching decompilation for the USA release. This import contains C recovered with N64 Decomp Kit, Round 12 (lab commit `9ed9048`). An independent rebuild and verification replay passed for every published C match.

| Metric | Verified | Catalogued | Progress |
|---|---:|---:|---:|
| Matching C code bytes | 36,060 | 401,896 | 8.97% |
| Matching C functions | 237 | 777 | 30.50% |
| Matching C bytes in the verified pinned link | 36,060 | 401,896 | 8.97% |

These measurements cover an incomplete function catalogue. GNU ld linked all 237 verified C units into a pinned mixed image and the resulting cartridge matched the USA ROM byte for byte. The remaining ranges still use local ROM extraction. Whole-title source reconstruction remains incomplete. See the [link verification record](docs/pinned-link.md) and the [machine-readable report](decomphub.progress.json).

[ByteMatch](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64) receives the same scoped figures under the `usa-catalogued` version.

[![Matching C bytes in the catalogue](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64.svg?version=usa-catalogued&category=catalogued-code&measure=matched_code_percent&label=Catalogued%20C%20bytes)](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64/usa-catalogued)

ByteMatch's fuzzy score is a lower bound based on exact matches. Partial similarity is unmeasured. Its fully linked figure counts only verified C bytes linked into the mixed image.

- ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`
- ROM size 4,194,304 bytes
- `src/main/` contains the verified function sources.
- `MATCHED.tsv` records image, address, owned code size, and recipe for each source.

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
