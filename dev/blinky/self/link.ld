ENTRY(_reset);

MEMORY {
	flash(rx) : ORIGIN = 0x08000000, LENGTH = 512K
	sram(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_estack = ORIGIN(sram) + LENGTH(sram);

SECTIONS {
	.vectors	:	{ KEEP(*(.vectors)) }	> flash
	.text		:	{ *(.text*) }		> flash
	.rodata		:	{ *(.rodata*) }		> flash

	.data : {
		_sdata = .;
		*(.data SORT(.data.*))
		_edata = .;
	} > sram AT > flash
	_sidata = LOADADDR(.data);

	.bss : {
		_sbss = .;
		*(.bss SORT(.bss.*) COMMON)
		_ebss = .;
	} > sram
}

