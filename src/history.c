#include "inc/history.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* history_fd;

void history_init() {
	char filename[256];
	const char *home = getenv("HOME");
	strcpy(filename, home);
	strcat(filename, "/.sesh_history");
	history_fd = fopen(filename, "a+");
}

void history_cmd(int argc, char** argv) {
	int count=0;
	char str[50];
	if (history_fd==NULL) {
		puts("History is empty.");
	} else {
		printf("This is history:\n");
		fseek(history_fd, 0, SEEK_SET);
		while (fgets(str, 50, history_fd) != NULL) {
			count++;
			printf("%d %s",count, str);
		}
		puts("");
	}
}

void history_save_cmd(char* cmd) {
	if (history_fd == NULL) {
		puts("Problems!");
	} else {
		fseek(history_fd, 0, SEEK_END);

		fputs(cmd, history_fd);
		fputs("\n", history_fd);
	}
}
