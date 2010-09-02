/* LPC2368 Memory Definitions */
MEMORY
{
  ROM (rx) : ORIGIN = 0x00000000, LENGTH = (512k-8k)	/* Flash: 512k - boot code */
  RAM (w) : ORIGIN = 0x40000000, LENGTH = (32k-32)	/* SRAM: 32k - IAP work */
  URAM (w) : ORIGIN = 0x7FD00000, LENGTH = (8k)		/* USB RAM: 8k */
  ERAM (w) : ORIGIN = 0x7FE00000, LENGTH = (16k)	/* Ethernet RAM: 16k */
  BRAM (w) : ORIGIN = 0xE0084000, LENGTH = (2k)		/* Battery RAM: 2k */
}


/* Section Definitions */
SECTIONS
{
  /* The first section which is used for code */
   .text :
  {
	KEEP(*(.VECTOR))	/* Exception vector table */
	*(.text .text.*)	/* Program code */
	*(.gnu.linkonce.t.*)
	*(.glue_7)
	*(.glue_7t)
	*(.gcc_except_table)
	*(.rodata)		/* Read-only data (constants) */
	*(.rodata*)
	. = ALIGN(4);
	__text_end__ = . ;
  } > ROM


  /* .data section which has initialized data */
  /* Located in RAM but loaded to end of .text */
  /* This section will be initialized with ROM data by startup code */
  .data : AT (__text_end__)
  {
	__data_start__ = . ;
	*(.data)
	*(.data.*)
	. = ALIGN(4);
	__data_end__ = . ;
  } > RAM


  /* .bss section which is initialized to zero */
  /* This section will be filled with zero by startup code */
  .bss (NOLOAD) :
  {
	__bss_start__ = . ;
	*(.bss)
	*(.bss.*)
	*(COMMON)
	. = ALIGN(4);
	__bss_end__ = . ;
  } > RAM


  .stack (NOLOAD) :
  {
	__stack_start__ = . ;
	KEEP(*(.stack .STACK))
	. = ALIGN(4);
	__stack_end__ = . ;
  } > RAM


  .usbram (NOLOAD) :
  {
	__usbram_start__ = . ;
	*(.usbram)
	. = ALIGN(4);
	__usbram_end__ = . ;
  } > URAM


  .etherram (NOLOAD) :
  {
	__etherram_start__ = . ;
	*(.etherram)
	. = ALIGN(4);
	__etherram_end__ = . ;
  } > ERAM


  .batteryram (NOLOAD) :
  {
	__batteryram_start__ = . ;
	*(.batteryram)
	. = ALIGN(4);
	__batteryram_end__ = . ;
  } > BRAM


  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}
