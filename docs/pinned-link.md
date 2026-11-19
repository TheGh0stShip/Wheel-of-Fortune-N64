# USA pinned-link verification

- Reference ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`.
- Input C source is the final Round 12 `wof24d` export. Its function inventory, immutable source digests, recipes, and provenance are recorded in `MATCHED.tsv` and `progress-inventory.tsv`.
- GNU MIPS linker via N64 Decomp Kit Round 12. The kit generated the pinned layout and ran `relink-cartridge --linker gnu-ld` with the matching local ROM project.
- GNU ld exited zero. Cartridge SHA-1 matched the input ROM and all 4,194,304 bytes compared equal. The link report recorded zero holes, unresolved symbols, pin conflicts, spills, or overlaps.
- 749 strictly replayed C functions contribute 396,708 owned code bytes. Six formerly symbol-blocked library functions are now linked from C using the reviewed addresses in `config/reviewed_symbols.txt`.
- Every one of the 775 catalogued function ranges now has verified source. The remaining 26 ranges are architecture-specific assembly or GCC runtime source containing inline assembly, so they are excluded from matching-C credit. `source-accounted.tsv` hashes every published source.
- All 618 link units now come from source; no raw function-unit stand-ins remain. Original placement freedom remains unverified.

[`progress-linked.tsv`](../progress-linked.tsv) records each credited unit's image, linked address, owned size, and verified source digest. The report generator checks it against the published function inventory before granting linked credit.

[`RELINK.json`](../RELINK.json) is the machine-readable exact-link receipt. It records an identical outcome, no holes, no overlaps, no spills, and no link problems. The full cartridge comparison reported zero differing bytes and the reference SHA-1 above.
