#ifndef __OS__
	#define __OS__
	//stack adx, task control block 
	typedef struct tcb{
		//datatypes with fixed number of size, not like int that change based on language
		uint32_t *sp; //pointer stack
		const char *name;
	} tcb_t;
	//extern  can be used in every .c program where .h is included
	extern tcb_t task1_tcb;
	extern tcb_t task2_tcb;


	/*extra parameters (*) Initialize task stack so that a future os_switch will "return" into entry() */
	void os_init_task(tcb_t *tcb, uint32_t *stack_base, uint32_t stack_words, void (*entry)(void), const char *name);

	/* Start first task (calls os_switch with current=NULL -> next=task1) */
	void os_start(tcb_t *first);

	/* Voluntary yield to the other task, switch to other task */
	void os_yield(void);

	/* Called if a task returns; loops yielding forever */
	void os_task_exit(void);

#endif
