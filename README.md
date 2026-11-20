# Wheel of Fortune (Nintendo 64, USA): matching decompilation

A work-in-progress reconstruction of the USA release (ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`,
4,194,304 bytes). Supply your own ROM; it is never committed.

## Progress

Both numbers come from `./wof report`, which rebuilds every unit with the original compiler, links an image and
requires its SHA-1 to equal the retail ROM's.

| measure | functions | of |
|---|---:|---:|
| **Matched under the rules** (byte-identical and passing every [match] code rule) | **4** | 775 |
| Bytes matched (byte-identical at the gate) | 443 | 775 |

- 443 units (323,328 of 402,772 code bytes) rebuild byte-identical: all 441 game functions and two libgcc wrappers.
- 439 of those are `MATCH-PENDING`: the bytes are right but the source is machine-lifted C with no shared
  headers, per-file copies of types and globals, and stand-in locals. That is open work, not progress.
- 307 units are open: the library (libultra) units, whose build recipe is not yet
  established.
- 25 function ranges are assembly and are not yet built from source here.

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
