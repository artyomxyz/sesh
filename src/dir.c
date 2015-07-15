#include "inc/dir.h"

#include <unistd.h>
#include <stdio.h>

void dir_cmd(int argc, char** argv) {
	int i = chdir(argv[1]);
	if (i != 0) {
		puts("\nUnable to change directory");
	}
};