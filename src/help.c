#include "inc/help.h"

#include <stdio.h>
/* Description:
*	It displays a brief description of the program.	
*  Receives:
*	int argc - The number of arguments of the interpreter.
*	char** argv - A pointer to an array of strings consisting of these arguments. 
*  Returnes: 
*	void
*/

void help_cmd(int argc, char** argv) {
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
