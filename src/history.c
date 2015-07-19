#include "inc/history.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* history_fd;

/* Description:
* 	Provides opening the file with a history of commands entered.
*  Receives:
*	void
*  Returnes: 
*	void
*/
char *history_entries[1000];
int hist_count=0;

void history_init() {
	char filename[256];
	const char *home = getenv("HOME");
	strcpy(filename, home);
	strcat(filename, "/.sesh_history");
	history_fd = fopen(filename, "a+");
	while (1) {
	 	char* cmd=(char *)malloc(sizeof(char)*256);
	 	
	 	if (fgets(cmd, 256, history_fd) != NULL) {
	 		free(cmd);
	 		break;	 		
	 	}
	 	history_entries[hist_count++]=cmd;
	 	printf("%s\n",cmd);
		//printf("%d %s",count, str);
			
	}
	printf("%d\n",hist_count);
}
/* Description:
* 	The function of outputting of history from file. 
*  Receives:
*	int argc - The number of arguments of the interpreter.
*	char** argv - A pointer to an array of strings consisting of these arguments.	
*  Returnes: 
*	void
*/

void history_cmd(int argc, char** argv) {
	int count=0;
	char str[256];
	if (history_fd==NULL) {
		puts("History is empty.");
	} else {
		printf("This is history:\n");
		fseek(history_fd, 0, SEEK_SET);
		while (fgets(str, 256, history_fd) != NULL) {
			count++;
			printf("%d %s",count, str);
		}
		puts("");
	}
}
/* Description:
*	The function of adding command in history.
*  Receives:
*	char* cmd - the pointer to the command.
*  Returnes: 
*	void
*/	
void history_save_cmd(char* cmd) {
	if (history_fd == NULL) {
		puts("Problems!");
	} else {
		fseek(history_fd, 0, SEEK_END);

		fputs(cmd, history_fd);
		fputs("\n", history_fd);
	}
}

/* Description:
*	The function of finding command in the history from the input number.
*  Receives:
*	int i - number of required command
*  Returnes: 
*	his_entry - a pointer to the command
*/

char history_entry_buff[256];
char* history_entry(int i) {
	return history_entries[hist_count-i-1];	
}
