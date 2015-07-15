#include <inc/ls.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

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