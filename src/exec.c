#include "inc/exec.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

void cmd_exec(int _argc, char** _argv) {
	pid_t p;
	p=0;
	p=fork();
	int* status;
	wait(status);
	if (p==0){
		if (execvp(_argv[0],_argv)==-1){
			printf("No such file: %s\n", _argv[0]);
		}
		exit(-1);
	}
}