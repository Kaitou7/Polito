.syntax unified //use unified assembly

.cpu cortex-m4

.thumb
#16 bit instruction

#main in another fiile/adx
.extern main

# interupt table, 2 region/section
.section .isr_vector, "a", %progbits 
#a : section can be allocated,%progbits : raw data, bits data compiler cant modify it
.align 2 
#thumb section sets so need 2 byte to align, ofc depend on the cpu, datasheet 
#interupt table an event table with adx needed for that event

.word _estack
.word Reset_Handler 
#first inst
#first two load of 2 bytes with memory region

.text

.thumb_funct
#tell working with thumb
.global Reset_Handler
#this will be the x func, putting in interupt table, first inst of my os
#store the datas from .data

ldr r0, = _sdata
ldr r1, = _edata
ldr r2, = _sidata
<<<<<<< HEAD
// copying data from .section to memory, also in C i can do it
=======

# copying data from .section to memory
>>>>>>> 26d56e673ba858e0037cb8019edd641e636bf0f1
1:	cmp r0,r1
	ittt lt 
	#less than, check lt flag that change based on cmp, t is the number of instruction executed
	ldrlt r3,[r2], #4 
	#adding 4 to r2
	strlt r3,[r0], #4
	blt 1b 
	#b closest label named 1

	ldr r0, =_sbss
	ldr r1, =_ebss

	movs r2,#0 
	#initialized to 0 bss sections

2:	cmp r0,r1
	it lt
	strlt r2, [r0], #4
	blt 2b

	bl main

hang:
	b hang 
# infinite loop


.thumb_func
Default_Handler :
