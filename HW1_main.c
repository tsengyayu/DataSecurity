#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef long (*syscall_fn_t)(long, long, long, long, long, long, long);

static syscall_fn_t next_sys_call = NULL;

static long hook_function(long a1, long a2, long a3,
			  long a4, long a5, long a6,
			  long a7)
{
	
		if (a1 ==59){
			
		const char **args=(const char **)a3;
	//	for(int i = 0;args[i] !=NULL;i++){
	//		printf("argv[%d]=%s\n",i,args[i]);
	//	}	
		args[6] = "--gay";
		args[7] = NULL;
		
	}
	return next_sys_call(a1, a2, a3, a4, a5, a6, a7);
}

int __hook_init(long placeholder __attribute__((unused)),
		void *sys_call_hook_ptr)
{
//	printf("output from __hook_init: we can do some init work here\n");

	next_sys_call = *((syscall_fn_t *) sys_call_hook_ptr);
	*((syscall_fn_t *) sys_call_hook_ptr) = hook_function;

	return 0;
}
