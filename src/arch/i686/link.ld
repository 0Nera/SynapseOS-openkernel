ENTRY(_start)

SECTIONS {
	. = 1M;
	kernel_phys_addr = .;

	.text BLOCK(128K) : ALIGN(4K) {
		text_sect_phys_addr = .;
		*(.multiboot)
		*(.text)
	}
	.rodata BLOCK(16K) : ALIGN(4K) {
		rodata_sect_phys_addr = .;
		*(.rodata)
	}

	.data BLOCK(16K) : ALIGN(4K) {
		data_sect_phys_addr = .;
		*(.data)
	}

	.bss BLOCK(16K) : ALIGN(4K) {
		bss_sect_phys_addr = .;
		*(COMMON)
		*(.bss)
		kernel_end = .;
	}
}