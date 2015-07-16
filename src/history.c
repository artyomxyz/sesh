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
void history_init() {
	char filename[256];
	const char *home = getenv("HOME");
	strcpy(filename, home);
	strcat(filename, "/.sesh_history");
	history_fd = fopen(filename, "a+");
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
	char str[50];
	if (history_fd==NULL) {
		puts("History is empty.");
	} else {
		printf("This is history:");
		fseek(history_fd, 0, SEEK_SET);
		while (fgets(str, 50, history_fd) != NULL) {
			printf("%s",str);
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
char* history_entry(int i)
{
	char* his_entry = NULL;
	int count = 0;
	char str[256];
	if (history_fd == NULL) {
		puts("Problems!");
	} else {
		while (fgets(str, 256, history_fd) != NULL) {
			count++;
			if (count == i) {
				his_entry = str;
				break;
			}
		}
	}
	fclose(history_fd);
	return(his_entry);
}
