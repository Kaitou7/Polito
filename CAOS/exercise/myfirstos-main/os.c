#include "os.h"
#include <stdint.h>
#include <stddef.h>
#include "library.h"
// pointer to first instruction of the program (*entry)(void)
// pointer of the program we want to run, address of stack pointer, size of stack,pointer of the program i want to run with return void and parameter void ,name.

static tcb_t *current = 0;
// current task pointed.

tcb_t task1_tcb = {0,"task1"};
tcb_t task2_tcb = {0,"task2"};

void os_switch(tcb_t **pcurrent, tcb_t *next);
// done on assembly but can be done in assembly, here defined in another file.


void os_init_task(tcb_t *tcb, uint32_t *stack_base, uint32_t stack_words, void (*entry)(void), const char *name){

	uint32_t *sp = stack_base + stack_words;
// stack at the end of sp, that how it works
//align the stack in case stack_words is not multiple of 4
	sp = (uint32_t *)((uintptr_t)sp & ~(uintptr_t)0x7);
	// last 3 bit equal to 0
	//save some space for registers 9, r3-r12, r0-r2 not used for something to preserve
	sp -= 9; //8 + sp register, i move 9 space of 32bit before.

	for (int i=0; i<8; i++){
		sp[i] = 0xDEADBEEF; // just for debugging and not with just 0, at the start must be 0 or what i want
	}

	sp[8] = ((uint32_t)entry) | 1u; //thumb mode must have last bit always assigned to 1

	tcb->sp= sp;
	tcb->name= name;
}
//called fork or initialize task

void os_start(){

	os_switch(&current,first); //internal func, (pointer current running program and tcb of next task want to start)

	while(1); //infinity loop so we never finish, also prevent running random code.
}

void os_yield(void)
{
	os_switch(&current, other_task()); //voluntary yield to other task
}

void os_task_exit(void){
	my_printf("task returned, yeld forever.");

	while(1){  
// im not sure there are no other program running, so i dont want my os power off and want to stay up with an infinite loop.
	os_yield();
}
}
