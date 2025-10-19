/* file: linker.ld 
 * author: Tzamn Melendez Carmona
 * version: 1.0
 * 
 * description: This file is the linker script for the netduinoplus2 board, for the qemu-arm
 * emulator. This file is used to define the memory regions of the board, this is a simple linker,
 * it only defines the memory regions for the text, data, bss and stack sections.
 */

/* define the memory regions */
/* ENTRY directive defines the entry point of the program */

ENTRY(Reset_Handler)
/*first inst will be compiled when cpu start*/

/* SECTIONS directive defines the memory regions of the program */

/*  memory from datasheet */


MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}


_estack = ORIGIN(RAM) + LENGTH(RAM);/* END OF RAM */



SECTIONS
{

    /* elf conf; interupt table; must be align to multiple of 4 byte; . is a section  */
    .isr_vector : ALIGN(4)
{
	/* this section must be there is private for him, no other instructio can get it  */
	KEEP(*(.isr_vector))
	
}> FLASH /*BEGINNING OF THE MEMORY (FLASH)*/



    /* text section (code)*/
    .text : ALIGN(4)
 {
	/*  place all section .text from .elf and put here, also ro datas also*/
	*(.text*);
	*(.rodata*);  /* read only */
	. =ALIGN(4);
 } > FLASH 		
    /* data section, initialized variables */
   
 .data : ALIGN(4)
{
 _sidata = LOADADDR(.data); /*symbol of address of data, will be useful later*/
 _sdata = . /*  symbol of initial data */
 *(.data);
 . = ALIGN(4);
 _edata = .; /* last adx of section, cause i need the size of the section */
 } > RAM AT > FLASH /* during exe will be in ram but initially at flash mem*/
    /* bss section, uninitialized variables */

 .bss (NOLOAD) : ALIGN(4)
{
 
 _sbss=.;
 *(.bss*);
 *(COMMON) /* extra space, variables generated auto by compiler gcc */
 . = ALIGN(4);
 _ebss = .;

 } > RAM

}

