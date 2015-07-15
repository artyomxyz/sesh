#include <stdio.h>
#include <deps/argtable3/argtable3.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/types.h>
#define maxargs 255

#include "inc/term.h"
#include "inc/repl.h"

/* Variables with information about cli arguments */
struct arg_lit *help, *version;
struct arg_end *end;

int main(int argc, char *argv[]) {
	/* Name of the programme */
	char progname[] = "sesh";
	char progversion[] = "0.1.0";

	/* Arguments table */
	void *argtable[] = {
		help    = arg_litn("h", "help", 0, 1, "Display this help and exit"),
		version = arg_litn("v", "version", 0, 1, "Display version info and exit"),
		end     = arg_end(20),
	};

	/* Number of errors analysing arguments */
	int nerrors = arg_parse(argc, argv, argtable);

	/* If help needed we don't care about the errors */
	if (help->count > 0) {
		printf("Usage: %s", progname);
		arg_print_syntax(stdout, argtable, "\n");
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 0;
	}

	/* If errors occured */
	if (nerrors > 0) {
		/* Displaying the error information */
		arg_print_errors(stdout, end, progname);
		printf("Try '%s --help' for more information.\n", progname);
		
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 1;
	}

	if (version->count > 0) {
		printf("Version: %s %s\n", progname, progversion);

		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 0;
	}

	term_set_driver();
	repl();	

	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;
}

void cmd_exec(int _argc, char** _argv) {
	pid_t p;
	p=0;
	p=fork();
	int* status;
	wait(status);
	if (p==0){
		if (execvp(_argv[0],_argv)==-1){
			printf("No such file: ");
			puts(_argv[0]);
		}
		exit(-1);
	}
}
