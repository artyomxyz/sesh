#include "inc/dir.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

char* autocomplete_array[256];
char autocomplete_buff[8192];
/* Description:
* 	Search all the options autocomplete. Formation of a string array of options.
*  Receives:
*	int argc - The number of arguments of the interpreter.
*	char** argv - A pointer to an array of strings consisting of these arguments.
*  Returnes: 
*	A pointer to an array of strings consisting of all possible options for autocompletion.
*/

char** autocomplete_find(char* f) {
	struct dirent *entry;
	char name_dir[256];

	int Wcounter = 0;
	int Scounter = 0;
	
	char pth[1024];
	char* path;
	path = pth;
	path = getenv("PATH");		

	int i = 0;
	int start = 0;
	int pathlenOrig = strlen(path);
	getcwd(name_dir, 256);
	
	*(path+pathlenOrig) = ':';
	while (name_dir[i] != '\0') {
		*(path+pathlenOrig+i+1) = name_dir[i];
		i++;
	}
	*(path+pathlenOrig+i+1) = '\0';

	int pathlen = strlen(path);
	for(i = 0; i<=pathlen; i++) {
		if ((*(path+i) == ':') || (*(path+i) == '\0')) {
		*(path+i) = '\0';

		DIR *dir = opendir(path+start);
		
		if(!dir) {
			autocomplete_array[0] = NULL;
			return autocomplete_array;
		}
		
		while((entry = readdir(dir)) != NULL) {
			int i = 0;
			int notPrefix = 0;
			while((f[i] != '\0')) {
				if(entry->d_name[i] != f[i]) {
					notPrefix = 1;
					break;
				}
				if(entry->d_name[i] == '\0') {
					notPrefix = 1;
					break;
				}
				i++;
			}
			if(notPrefix == 0) {
				autocomplete_array[Wcounter++] = autocomplete_buff+Scounter;
				i = 0;
				while(entry->d_name[i]!=0) {
					autocomplete_buff[Scounter] = entry->d_name[i];
					Scounter++;
					i++;
				}
				autocomplete_buff[Scounter] = '\0';
				Scounter++;
			}
		}
		closedir(dir);	
		*(path+i) = ':';
		start = i + 1;
		}
	}
	*(path+pathlenOrig) = '\0';

	autocomplete_array[Wcounter] = NULL;

	return autocomplete_array;
}
