# Reviewed symbol addresses

Six library functions were previously byte-identical except for unresolved
addresses. The eleven declarations in `config/reviewed_symbols.txt` were
reconstructed from the address-forming instructions and section placement in
those units. Rebuilding with these declarations produces identical text, and
the final cartridge relink has zero differing bytes.

These six functions cover 2,664 bytes. Their matching-C classification is
conditional on the stated addresses. The instructions independently establish
the numeric values used by the link, but there is no independent Wheel of
Fortune symbol source confirming the donor-derived identifiers.

The names retain their donor-source spelling and are not independently proven
original Wheel of Fortune names. The addresses and placement are the verified
facts; future naming work may replace the identifiers without changing them.

Two declarations are section bases rather than ordinary symbols:

- `n64dk_section_80038998_bss = 0x800AFE60`
- `n64dk_section_8004AD58_data = 0x800850E8`

The complete reviewed list is kept as machine-readable linker syntax in
`config/reviewed_symbols.txt`.
