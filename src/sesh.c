#include <stdio.h>
#include <deps/argtable3/argtable3.h>

/* Variables that stores the information about command line arguments */
struct arg_lit *help, *version;
struct arg_end *end;

int main(int argc, char *argv[])
{
	/*  Argument Table */
	void *argtable[] = {
		help    = arg_litn("h", "help", 0, 1, "Display this help and exit"),
		version = arg_litn("v", "version", 0, 1, "Display version info and exit"),
		end     = arg_end(20),
	};

	/* Name of the programme */
	char progname[] = "sesh";
	char progversion[] = "0.0.0";

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

	if (version->count >0) {
		printf("Version: %s %s\n", progname, progversion);

		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 0;
	}

	printf("Hello, World!\n");
	
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;
}