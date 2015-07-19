#include "inc/dir.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

/* Description:
*	Moves user to the catalogue, that they enter.	
*  Receives:
*	int argc - The number of arguments of the interpreter.
*	char** argv - A pointer to an array of strings consisting of these arguments.	
*  Returnes: 
*	void	
*/

void dir_cmd(int argc, char** argv) {
	char* dir;

	if (argc == 1) {
		dir = getenv("HOME");
	} else {
		dir = argv[1];
	}

	int err = chdir(dir);
	if (err != 0) {
		printf("Unable to change directory, error: %d\n", err);
	}
}
/* Description:
*	It prints the contents of the specified folder.	
*  Receives:
*	int argc - The number of arguments of the interpreter.
*	char** argv - A pointer to an array of strings consisting of these arguments.	
*  Returnes: 
*	void
*/

void ls_cmd(int argc, char** argv) {
	struct dirent *entry;
	struct stat st;
	
	char name_dir[256];
	char full_name[256];
	
	if (argc==1) {
		getcwd(name_dir, 256);
	} else {
		if (argv[1][0] == '/') {
			strcpy(name_dir, argv[1]);
		} else {
			getcwd(name_dir, 256);
			strcat(name_dir, "/");
			strcat(name_dir, argv[1]);
		}
	}
	
	DIR *dir=opendir(name_dir);
	
	if (!dir) {
		printf("There is no such directory : \"%s\".\n", argv[1]);
	} else {
		while ( (entry = readdir(dir) ) != NULL) {
			if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
                continue;
			
			strcpy(full_name, name_dir);
			strcat(full_name, "/");
			strcat(full_name, entry->d_name);
			
			if(lstat(full_name, &st)){
				printf("%-30d unable to define attributes\n", entry->d_name);
			} else {
				switch(st.st_mode & S_IFMT){
					case S_IFLNK:
						printf("%-30s link\n", entry->d_name); break;
					case S_IFDIR:
						printf("%-30s directory\n", entry->d_name); break;
					case S_IFREG:
						printf("%-30s regular\t\t%d bytes\n", entry->d_name, st.st_size); break;
					case S_IFCHR:
						printf("%-30s device\n", entry->d_name); break;
					case S_IFBLK:
						printf("%-30s device\n", entry->d_name); break;
					case S_IFIFO:
						printf("%-30s FIFO\n", entry->d_name); break;
					case S_IFSOCK:
						printf("%-30s socket\n", entry->d_name); break;
					default:
						printf("%-30s undefined type\n", entry->d_name); break;
				}
			}	
		}
	}
	closedir(dir);
}
