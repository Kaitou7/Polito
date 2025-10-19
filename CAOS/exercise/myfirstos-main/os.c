#include "os.h"
#include <stdint.h>
#include <stddef.h>
// pointer to first instruction of the program (*entry)(void)
void os_init_task(tcb_t *tcb, uint32_t *stack_base, uint32_t stack_words, void (*entry)(void), const char *name){

	uint32_t *sp = stack_base + stack_words;
	//align the stack in case stack_words is not multiple of 4
	sp = (uint32_t *)((uintptr_t)sp & ~(uintptr_t)0x7);
	// last 3 bit equal to 0
	//save some space for registers 9, r3-r12, r0-r2 not used for something to preserve
	sp -= 9; //8 + sp register
	
	for (int i=0; i<8; i++){
		sp[i] = 0xDEADBEEF; // just for debugging and not with just 0
	}

	sp[8] = ((uint32_t)entry) | 1u; //thumb ist set last bit is always 1

	tcb->sp= sp;
	tcb->name= name;
}
//called fork or initialize task

void os_start(){

	os_switch(&current,first); //internal func, pointer running program and tcb of next task to start

	while(1);
}

void os_yield(void)
{
	os_switch(&current, other_task());
}
