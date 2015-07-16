#include "inc/exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
/* Description:
*	Run the file entered as an argument.
*	fork clone the process into two identical, the first primary, he has a pid (process identifier), the second child pid = 0.
*	If the process of the child (if p == 0), then it looks for a file with the name of which he applied to the input (argv [0]) in the *		directories or on the PATH, a direct address.
*
*  Receives:
*	int argc - The number of arguments of the interpreter.
*	char** argv - A pointer to an array of strings consisting of these arguments.
*  Returns: 
*	void
*/
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
