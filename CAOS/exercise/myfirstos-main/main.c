#include <stdint.h>
#include "os.h"
#include "library.h"

static uint32_t stack1[256];
static uint32_t stack2[256];
// stack assigned manually for our programs, stored in bss section.

extern void my_printf(const char *s);

static void task1(void){
// what our task1 do, just simply things
	while(1){
	my_printf("task 1 iteration \n");
	delay_cycles(150000);
	os_yeld(); //pass control to next program
	}
}

static void task2(void){
	while(1){
	my_printf("task 2 iteration \n");
	delay_cycles(150000);
	os_yeld();
	}
}

/* This is a function to print strings using UART */
int main(void) {

    my_printf ("Hello World");
// need to define memory/stack for our programs, we are os and we need to assign
    os_init_task(&task1_tcb,stack1,sizeof(stack1)/sizeof(stack1[0]),task1,"task1");
    os_init_task(&task2_tcb,stack2,sizeof(stack2)/sizeof(stack2[0]),task2,"task2");
    os_start(&task1_tcb);

    return 0;
}


