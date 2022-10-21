ENTRY(_start)

SECTIONS {
    KERNEL_BEGIN = .;
    KERNEL_BEGIN_PHYS = . - 0xC0000000;
    

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
		KERNEL_END = .;
	}

	KERNEL_SIZE = KERNEL_END - KERNEL_BEGIN;
}