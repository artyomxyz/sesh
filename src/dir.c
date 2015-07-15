#include "inc/dir.h"

#include <unistd.h>
#include <stdio.h>

void dir_cmd(int _argc, char** _argv) { 
	int i = chdir(_argv[1]);
	if (i != 0) {
		puts("\nUnable to change directory");
	}
};