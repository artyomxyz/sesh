#include "inc/dir.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

void dir_cmd(int argc, char** argv) {
	char* dir;

	if (argc == 1) {
		dir = getenv("HOME");
	} else {
		dir = argv[1];
	}

	int err = chdir(dir);
	if (err != 0) {
		printf("\nUnable to change directory, error: %d\n", err);
	}
}

void ls_cmd(int argc, char** argv) {
	struct dirent *entry;
	char name_dir[256];
	
	getcwd(name_dir, 256);
    DIR *dir=opendir(name_dir);
   
    if (!dir) {
        printf("Sorry, can' t do ls.");
    }

    while ( (entry = readdir(dir)) != NULL){
        printf("%s\n", entry->d_name);
    }
   
    closedir(dir);
}