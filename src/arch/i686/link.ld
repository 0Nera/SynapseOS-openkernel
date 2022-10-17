/* The bootloader will start execution at the symbol designated as the entry point. In this case, that's 'start' (defined in start.s) */
ENTRY(_start)
 
/* Tell the linker part of the compiler where the various sections of the kernel will be put in the final kernel executable. */
SECTIONS {
    . = 0x00200000;

    .text ALIGN (0x1000) :
    {
        *(.multiboot)
        *(.text)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
    /* */
    end = .; _end = .; __end = .;    
}