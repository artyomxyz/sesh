#include "inc/help.h"

#include <stdio.h>

void cmd_help(char* _str, char* _com) {
	char str[50];
	FILE *pfile;
	pfile = fopen("/usr/share/sesh/HELP","r");
	if (pfile==NULL) {
		puts("Sorry, help is unavailable now.");
	} else {
		puts("This is help:");
		while (fgets(str,50,pfile)!=NULL)
			printf("%s",str);
		fclose(pfile);
	}
}
