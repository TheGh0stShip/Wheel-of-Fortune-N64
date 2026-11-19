# USA pinned-link verification

- Reference ROM SHA-1 `b51b28660699bf029f862f51c319a5962fe9de9b`.
- Input C source import `18a801797939ab8f121ac51dcac1b3208e789f42`.
- GNU MIPS linker via N64 Decomp Kit Round 12 lab commit `3236819`. The kit generated the pinned layout with `decompile-project`, then ran `relink-cartridge --linker gnu-ld` with the matching local ROM project.
- GNU ld exited zero. Cartridge SHA-1 matched the input ROM and all 4,194,304 bytes compared equal. The link report recorded zero holes, unresolved symbols, pin conflicts, spills, or overlaps.
- 237 compiled C objects contributed 36,136 text bytes to the linked image. The tracker credits 36,060 owned code bytes and excludes the 76 additional alignment bytes.
- 540 remaining function ranges and other unresolved data were supplied from the local ROM. The reported percentage measures C integrated into this verified pinned image. Original placement freedom and a source-only build remain unverified.

[`progress-linked.tsv`](../progress-linked.tsv) records each credited unit's image, linked address, owned size, and verified source digest. The report generator checks it against the published function inventory before granting linked credit.
