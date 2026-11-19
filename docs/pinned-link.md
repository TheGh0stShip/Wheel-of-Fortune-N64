# USA pinned-link verification

- Reference ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`.
- Input source is the final Round 12 `wof27` export. Its function inventory, immutable source digests, recipes, and provenance are recorded in `MATCHED.tsv`, `progress-inventory.tsv`, and `source-accounted.tsv`.
- GNU MIPS linker via N64 Decomp Kit Round 12. The kit generated the pinned layout and ran `relink-cartridge --linker gnu-ld` with the matching local ROM project.
- GNU ld exited zero. Cartridge SHA-1 matched the input ROM and all 4,194,304 bytes compared equal. The link report recorded zero holes, unresolved symbols, pin conflicts, spills, or overlaps.
- 750 strictly replayed C functions contribute 396,752 owned code bytes. Six formerly symbol-blocked library functions are linked from C using the reviewed addresses in `config/reviewed_symbols.txt`; `func_80038718` (`__umoddi3`) is the final ordinary-C addition.
- Every one of the 775 catalogued function ranges has verified source. The 25 ranges outside the matching-C track are architecture-specific assembly or GCC runtime source containing inline MIPS assembly, so they are excluded from ordinary-C credit. `source-accounted.tsv` hashes every published source.
- All 618 link units now come from source; no raw function-unit stand-ins remain. Original placement freedom remains unverified.

[`progress-linked.tsv`](../progress-linked.tsv) records each credited unit's image, linked address, owned size, and verified source digest. The report generator checks it against the published function inventory before granting linked credit.

[`RELINK.json`](../RELINK.json) is the machine-readable exact-link receipt. It records an identical outcome, no holes, no overlaps, no spills, and no link problems. The full cartridge comparison reported zero differing bytes and the reference SHA-1 above.
