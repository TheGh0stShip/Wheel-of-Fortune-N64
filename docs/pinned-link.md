# USA pinned-link verification

- Reference ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`.
- Input source is the final Round 12 `wof27` export. Its function inventory, immutable source digests, recipes, and provenance are recorded in `MATCHED.tsv`, `progress-inventory.tsv`, and `source-accounted.tsv`.
- GNU MIPS linker via N64 Decomp Kit Round 12. The kit generated the pinned layout and ran `relink-cartridge --linker gnu-ld` with the matching local ROM project.
- GNU ld exited zero. Cartridge SHA-1 matched the input ROM and all 4,194,304 bytes compared equal. The link report recorded zero holes, unresolved symbols, pin conflicts, spills, or overlaps.
- 750 strictly replayed C functions contribute 396,752 owned code bytes. Six formerly symbol-blocked library functions are linked from C using the reviewed addresses in `config/reviewed_symbols.txt`; `func_80038718` (`__umoddi3`) is the final ordinary-C addition.
- Every one of the 775 catalogued function ranges has verified source. The 25 ranges outside the matching-C track are architecture-specific assembly or GCC runtime source containing inline MIPS assembly, so they are excluded from ordinary-C credit. `source-accounted.tsv` hashes every published source.
- All 618 link units now come from source; no raw function-unit stand-ins remain. Original placement freedom remains unverified.

## Evidence qualifications

- Six library functions, covering 2,664 bytes, depend on the eleven declarations in `config/reviewed_symbols.txt`. Their addresses and section placements are reconstructed from address-forming instructions in the units themselves; no independent Wheel of Fortune symbol source confirms the donor-derived names. The names are provisional and may be replaced without changing the verified addresses. See [`reviewed-symbols.md`](reviewed-symbols.md).
- The final six function-table rows—two C and four assembly—were entered manually rather than emitted by a kit run. Their evidence is the immutable per-source hashes, exact unit comparisons, the 618-of-618 source link, and the byte-identical cartridge receipt.
- The repository inventory is 775 disjoint ranges totaling 402,772 bytes. An external completion report quoted 402,816 bytes. No supplied `wof27` inventory supports that larger denominator: both `progress-inventory.tsv` and `wof27_full/FUNCTIONS.tsv` total 402,772. The 44-byte difference equals `func_80038718` (`__umoddi3`), consistent with that function being counted twice when the report combined its ordinary-C and compiler-runtime groups. The repository uses the disjoint inventory total.

[`progress-linked.tsv`](../progress-linked.tsv) records each credited unit's image, linked address, owned size, and verified source digest. The report generator checks it against the published function inventory before granting linked credit.

[`RELINK.json`](../RELINK.json) is the machine-readable exact-link receipt. It records an identical outcome, no holes, no overlaps, no spills, and no link problems. The full cartridge comparison reported zero differing bytes and the reference SHA-1 above.
