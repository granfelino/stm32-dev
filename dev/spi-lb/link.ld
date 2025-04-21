ENTRY(_reset);		/* define the entry point for the CPU -> the reset interrupt */


/* define memory regions available in the stm32 */
MEMORY {
	flash(rx) : ORIGIN = 0x08000000, LENGTH = 512K		/* flash: non-volatile memory -> data is safe between reboots;    slower access; more space */
	sram(rwx) : ORIGIN = 0x20000000, LENGTH = 128K		/* sram:  volatile memory	  -> data is cleared between reboots; faster access; less space */
}

/* stack is found at the end of the sram and grows downward, hence we define it at the end of the sram*/
_estack = ORIGIN(sram) + LENGTH(sram);


SECTIONS {
	.vectors :	{ KEEP(*(.vectors)) }	> flash			/* needed for booting up (the reset interrupt is found at the 1st (idx == 1) index of the interrupt vector) ; KEEP to tell the linker not to optimize the vector table out if unused, we need the reset to startup the board and it never changes */
	.text	 :	{ *(.text*) }		> flash				/* code of the program does not change at runtime -> no reason to put it in sram and use up valuable fast-access space */
	.rodata  :	{ *(.rodata*) }		> flash				/* read-only data (e.g. constants, string literals) -> does not change at runtime, no reason to put it in sram and use up the valuable fast-access space (not a lot of it is available) */

	.data : {
		_sdata = .;
		*(.data SORT(.data.*))
		_edata = .;
	} > sram AT > flash									/* we store the initial variable values here, to fetch them into sram at runtime -> we need initial values between reboots (hence stored in flash) and we need them in sram at runtime when the values change */
	_sidata = LOADADDR(.data);							/* in _sidata we store the address of the data in flash, to use it as a source from which we copy the values to sram */
	/* the _sdata and _edata variables are Virtual Memory Addresses (VMA) - the region which they define is reserved in SRAM, even though when MCU is booting up this region is empty */
	/* we use the LOADADDER(.data) to get the LMA (Loading Memory Address), where the .data is actually saved throughout booting cycles */
	/* we use _sidata to copy the contents of .data from flash to SRAM at runtime -> this is done in the _reset function */

	.bss : {
		_sbss = .;
		*(.bss SORT(.bss.*) COMMON)
		_ebss = .;
	} > sram											/* uninitialized global and static variables; they are needed at runtime -> hence sram; they are zeroed out at runtime in the init of the processor in the _reset() function */
}
