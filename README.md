# Wheel of Fortune (Nintendo 64, USA): matching decompilation

A work-in-progress reconstruction of the USA release (ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`,
4,194,304 bytes). Supply your own ROM; it is never committed.

## Progress

Both numbers come from `./wof report`, which rebuilds every unit with the original compiler, links an image and
requires its SHA-1 to equal the retail ROM's.

| measure | C functions | of |
|---|---:|---:|
| **Matched under the rules** (byte-identical and passing every [match] code rule) | **746** | 746 |
| Bytes matched (byte-identical at the gate) | 746 | 746 |

- Every code range of the image now builds from source: 369 units, 402,756 of 402,756 code bytes, covering all
  773 inventoried function ranges (745 C, 28 original assembly).
- The game is 441 functions built with GCC 2.7.2. All 441 pass the rules. The MPEG player is the Berkeley
  `mpeg_play` decoder, rebuilt as its 13 original objects with that source's names as `guess:`. The rest of
  the game is named where the evidence allows: 30 names the ROM's own messages record, 46 from the SDK demos'
  lineage, and 934 invented from what the code does, each listed with its evidence in `config/names.tsv`;
  about 30 functions whose purpose is unclear keep their placeholder names. Twelve of the game's original objects
  are rebuilt as units (191 functions); `./wof unitmap` prints the evidence for the rest, whose boundaries are
  not settled, and those functions still sit one per file.
- The library is libultra (IDO 5.3, built from the `ultralib` reconstruction under `lib/ultralib`) and three
  libgcc functions: 305 C functions, all of which pass the rules.
- Data: the gate links 250,561 data bytes from source, defined in the units that own them (the puzzles, the
  camera paths, the menu and stage tables, the clip masks, and so on). The SDK's RSP microcode, 18,880 bytes,
  is linked whole as the SDK shipped it: the build takes those bytes from your ROM and counts them apart, as
  asset bytes. 2,811 bytes still come from the ROM, data whose owning object is not settled yet;
  `./wof datamap` accounts for each of them by range, kind and candidate owner (`config/data.tsv`).

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
