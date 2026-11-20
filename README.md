# Wheel of Fortune (Nintendo 64, USA): matching decompilation

A work-in-progress reconstruction of the USA release (ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`,
4,194,304 bytes). Supply your own ROM; it is never committed.

## Progress

Both numbers come from `./wof report`, which rebuilds every unit with the original compiler, links an image and
requires its SHA-1 to equal the retail ROM's.

| measure | C functions | of |
|---|---:|---:|
| **Matched under the rules** (byte-identical and passing every [match] code rule) | **276** | 763 |
| Bytes matched (byte-identical at the gate) | 763 | 763 |

- Every code range of the image now builds from source: 598 units, 402,756 of 402,756 code bytes, covering all
  773 inventoried function ranges (745 C, 28 original assembly).
- The game is 441 functions built with GCC 2.7.2. 439 of them are `MATCH-PENDING`: the bytes are right but the
  source is machine-lifted C with no shared headers, per-file copies of types and globals, and stand-in locals.
  That is open work, not progress.
- The library is libultra (IDO 5.3, built from the `ultralib` reconstruction under `lib/ultralib`) and three
  libgcc functions. Nearly all of the functions that pass the rules today are library functions, not game code;
  48 library functions are `MATCH-PENDING`.
- Data is not reconstructed: outside the code, about 270,000 bytes of the image still come from the ROM.

Earlier versions of this file described the project as complete. That claim rested on ledgers produced by a
toolchain that is not in this repository (`MATCHED.tsv`, `progress-*.tsv`, `source-accounted.tsv`,
`RELINK.json`, `CARTRIDGE.json`, `docs/`, `proofs/`). Those files are kept as received and are not maintained.

## Building

The compiler runs under WSL. See [AGENTS.md](AGENTS.md) for the toolchain, the commands and the code rules.

```sh
./wof gate      # rebuild everything and compare with the ROM
./wof report    # the gate's result, then both progress numbers
./wof rules -v  # every code-rule finding
```
