#include <stdio.h>
#include <deps/argtable3/argtable3.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define STDIN_FILENO 0

/* Declaration of tty control structures */
struct termios old_tty, new_tty;
/* Variables with information about cli arguments */
struct arg_lit *help, *version;
struct arg_end *end;

char* dir[256];

//protipes
void set_driver();
void reset_driver();
void read_str(char* _str, char* _com);
void cmd_cd(char* _str, char* _com);
void cmd_cd_dir(char* _str, struct shell_state * dir);
void cmd_history(char* _str, char* _com);
void save_cmd_in_history(char* _com);
void cmd_help(char* _str, char* _com);
void cmd_exec(char* _str, char* _com);

int main(int argc, char *argv[]) {
	/* Argument table */
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

	if (version->count > 0) {
		printf("Version: %s %s\n", progname, progversion);

		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 0;
	}

	set_driver();
	
//main lex
	char typecom[][8] = { "cd", "history", "help", "exit" };
	void(*arr_func[])(char*, char*) = { cmd_cd, cmd_history, cmd_help};



	int i = 0;
	char com[80], str[80];	

	getcwd(dir, 256);
	printf("directory: ");
	puts(dir);	
	

	do {
		printf("%s > ", dir);

		read_str(str, com);
		save_cmd_in_history(com);
		for (i = 0; i < 4; i++) {
			if (strcmp(com, typecom[i]) == 0) {
				arr_func[i](str, com);
				break;
			}
		}

		if (i == 4) {
			cmd_exec(str, com);
		}
		
		
	} while (strcmp(com, typecom[3]) != 0);

	

	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;

}

void set_driver() {
	tcgetattr( STDIN_FILENO, &old_tty);
	new_tty = old_tty;
	new_tty.c_lflag &= ~(ICANON|ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &new_tty);

}

void reset_driver() {
	tcsetattr( STDIN_FILENO, TCSANOW, &old_tty);
}
//funct	
void read_str(char* _str, char* _com) {

	int i = 0;

	//echo on
	
	
	do {
		_str[i] = getchar();
		putchar(_str[i]);
		i++;
	} while ((int)_str[i - 1] != 10);
	_str[i - 1] = NULL;


	i = 0;
	while ((_str[i] != ' ') && ((int)_str[i] != NULL))
	{
		_com[i] = _str[i];
		i++;
	}
	_com[i] = NULL;
	puts(_com);
}

void cmd_cd(char* _str, char* _com) 
{ 
	int i = chdir(_str+3);
	if (i == chdir(_str+3))
		printf("\nnot moved\n");
};

void cmd_history(char* _str, char* _com)
{
	char str[50];
	FILE *pfile;
	pfile=fopen(".sesh_history","r");
	if (pfile==NULL)
	{
		puts("History is empty.\n");
	}
	else
	{
		printf("This is history:\n");
		while (fgets(str,50,pfile)!=NULL)
 		{
			printf("%s",str);
		}
	}
	fclose(pfile);
}
void save_cmd_in_history(char* _com)
{
	FILE *pfile;
	pfile=fopen(".sesh_history","a");
	if (pfile==NULL)
	{
		puts("Problems!\n");
	}
	fputs(_com,pfile);
	fputs("\n",pfile);
	fclose(pfile);
}
void cmd_help(char* _str, char* _com) { printf("This is help\n"); };
void cmd_exec(char* _str, char* _com) { printf("This is exec\n"); };
