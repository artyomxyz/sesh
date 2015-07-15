#include "inc/exec.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

void exec_cmd(int argc, char** argv) {
	pid_t p;
	p=0;
	p=fork();
	int* status;
	wait(status);
	if (p==0){
		if (execvp(argv[0], argv)==-1){
			printf("No such file: (%s)\n", argv[0]);
		}
		exit(-1);
	}
}