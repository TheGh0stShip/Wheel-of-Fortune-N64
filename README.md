# Wheel of Fortune (Nintendo 64)

Matching decompilation for the USA release. This initial import contains 237 C functions recovered from the ROM with N64 Decomp Kit, Round 12 (lab commit `9ed9048`). An independent rebuild and verification replay passed for every exported C match. The matching catalogue is incomplete. The 237 matches cover 30.5% of its 777 entries.

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
