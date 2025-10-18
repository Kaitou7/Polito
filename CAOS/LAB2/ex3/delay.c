#include "delay.h"

void delay_routine_1(){
	asm(
"mov r1,r0 \n"
"loop: \n"
"SUB R1,R1,#1 \n"
"CMP R1,#0 \n"
"BNE loop \n");
}

void delay_routine_2(unsigned int delay_counter) {
  asm("mov r1,r0 \n"
      "delay: \n"
          "subs r1, #1 \n"
          "bne delay \n"
      );
}

