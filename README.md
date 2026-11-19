# Wheel of Fortune (Nintendo 64)

Matching decompilation for the USA release. This import contains C recovered with N64 Decomp Kit, Round 12 (lab commit `9ed9048`). An independent rebuild and verification replay passed for every published C match.

| Metric | Verified | Catalogued | Progress |
|---|---:|---:|---:|
| Matching C code bytes | 36,060 | 401,896 | 8.97% |
| Matching C functions | 237 | 777 | 30.50% |

Both measurements cover an incomplete function catalogue. Whole-title completion and full ROM relinking are unmeasured. The [machine-readable progress report](decomphub.progress.json) is generated from [the inventory](progress-inventory.tsv) and the verified source manifest.

- ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`
- ROM size 4,194,304 bytes
- `src/main/` contains the verified function sources.
- `MATCHED.tsv` records image, address, owned code size, and recipe for each source.

The sources are standalone matching units. A complete ROM build is still pending. Supply your own USA ROM and the applicable compiler tools to reproduce a match. This repository contains C sources and verification metadata.

With N64 Decomp Kit, initialize a local project, then check a function using its row in `MATCHED.tsv`:

```sh
n64dk decompile-init 'Wheel of Fortune (USA).z64' --out local-project
n64dk match --project local-project --image-name main --no-infer \
  --addr 0x80002348 --size 0x250 --pipeline kmc+asn64 \
  --flags="-O0 -G0 -mips3 -mgp32 -mfp32" \
  --symbols survey/symbol_addrs.txt --symbols survey/sdk_symbols.txt \
  src/main/func_80002348.c
```
