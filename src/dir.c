#include "inc/dir.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

void dir_cmd(int argc, char** argv) {
	if (argc == 1)
	{
		int i = chdir(getenv("HOME"));
		if (i != 0) {
			puts("\nUnable to change directory");
		}
/*		char* p;
		p = getenv("HOME");
		chdir(p);
*/		
	}	
	else
	{
		int i = chdir(argv[1]);
		if (i != 0) {
			puts("\nUnable to change directory");
		}
	}
}

void ls_cmd(int argc, char** argv) 
{
	struct dirent *entry;
	char name_dir[256];
	
	getcwd(name_dir, 256);
    DIR *dir=opendir(name_dir);
   
    if (!dir)
        printf("Sorry, can' t do ls.");

    while ( (entry = readdir(dir)) != NULL)
        printf("%s\n",entry->d_name);
   
    closedir(dir);
}