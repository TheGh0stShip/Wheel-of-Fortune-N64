# Wheel of Fortune (Nintendo 64) — 100% decompiled and byte-identical

Complete matching-source reconstruction of the USA release. Every catalogued function is reproduced from machine-generated C that was subsequently cleaned and byte-verified, compiler-runtime source, or original assembly. All 618 source units relink into a cartridge that is byte-identical to the retail ROM; no raw function stand-ins remain.

| Completion metric | Verified | Catalogued | Progress |
|---|---:|---:|---:|
| **Functions reproduced from source** | **775** | **775** | **100.00%** |
| **Code bytes reproduced and fully linked from source** | **402,772** | **402,772** | **100.00%** |
| Matching C code bytes | 396,752 | 402,772 | 98.50% |
| Matching C functions | 750 | 775 | 96.77% |

**This decompilation is complete:** 775 of 775 functions have verified source, 775 of 775 ByteMatch units are complete, and 402,772 of 402,772 catalogued code bytes are fully linked from source. The resulting cartridge matches the USA ROM byte for byte. ByteMatch separately reports 98.50% as ordinary matching C because 20 routines were assembly in the original software and GCC's `__udivmoddi4` runtime requires inline MIPS assembly. Relabeling those routines as ordinary C would falsify their provenance; it does not represent unfinished decompilation work. See the [link verification record](docs/pinned-link.md) and [machine-readable report](decomphub.progress.json).

[ByteMatch](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64) receives the same scoped figures under the `usa-catalogued` version.

[![Source-reproduced code](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64.svg?version=usa-catalogued&category=catalogued-code&measure=complete_code_percent&label=Source-reproduced%20code)](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64/usa-catalogued)
[![Matching C bytes](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64.svg?version=usa-catalogued&category=catalogued-code&measure=matched_code_percent&label=Matching%20C%20bytes)](https://bytematch.dev/TheGh0stShip/Wheel-of-Fortune-N64/usa-catalogued)

On ByteMatch, **Units complete: 775 of 775** and **Fully linked: 100.00%** are the completion measurements. Gray segments in its unit heat map denote exact assembly/runtime source excluded from the ordinary-C score; they do not denote missing or raw functions. ByteMatch's fuzzy score is a lower bound based on exact C matches because partial similarity is unmeasured.

The matching C is not presented as fully human-reviewed or portable source. A byte-preserving cleanup removed all 442 pasted m2c compatibility preludes and substantially reduced lifted types, casts, empty prototypes, helper structs, and control-flow scaffolding. Remaining type recovery and shared-header work is recorded in the [source-cleanup report](docs/source-cleanup.md).

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
