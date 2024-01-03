SECTIONS {
    . = 0x80200000,
    kernel_entry = .;
    _s_kernel = .;

    _s_text_boot = .;
    .text.boot : {
        *(.text.boot)
    }
    _e_text_boot = .;

    _s_text = .;
    .text : {
        *(.text)
    }
    _e_text = .;

    _s_rodata = .;
    .rodata : AT(ADDR(.rodata)) {
        *(.rodata)
    }
    _e_rodata = .;

    _s_data = .;
    .data : {
        *(.data)
    }
    _e_data = .;

    . = ALIGN(0x8);
    _s_bss = .;
    .bss : {
        *(.bss*)
    }
    _e_bss = .;
    _e_kernel = .;
}