
void delay_routine_1(){
	asm(
"loop: \n"
"SUB R1,R1,#1 \n"
"CMP R1,#0 \n"
"BNE loop \n"
"add r4,r4,#4 \n");
}

