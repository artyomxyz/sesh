#include <stdio.h>
#include <deps/argtable3/argtable3.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

/* Declaration of tty control structures */
struct termios _savetty;
struct termios _tty;
/* Variables with information about cli arguments */
struct arg_lit *help, *version;
struct arg_end *end;


struct shell_state
{
	char* pwd;
};
struct shell_state cur_dir;

//protipes
void change_driver(struct termios* savetty,struct termios* tty);
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

	change_driver(&_savetty, &_tty);
	
//main lex
	char typecom[][8] = { "cd", "history", "help", "exit" };
	void(*arr_func[])(char*, char*) = { cmd_cd, cmd_history, cmd_help};



	int i = 0;
	char com[80], str[80];
	char dir[80] = "c:/mycode"; /* start */
	cur_dir.pwd = dir;


	do {
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

	/* exit */

	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;
}

void change_driver(struct termios* savetty,struct termios* tty) {
	if ( !isatty(0) ) { /*Check if stdin is terminal ?*/
		fprintf (stderr, "stdin not terminal\n");
		exit (1); /* stdin is file or smth. */
 	};

	tcgetattr(0, tty);
	savetty = tty; /* Save canonical mode info */
	tty->c_lflag &= ~(ICANON|ECHO|ISIG);
	tty->c_cc[VMIN] = 1;
	tcsetattr(0, TCSAFLUSH, tty);
}

//funct	
void read_str(char* _str, char* _com) {

	int i = 0;

	do {
		read(0, &_str[i],1);
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
	printf("This is cd\n"); 
	cmd_cd_dir(_str, &cur_dir); 
};

void cmd_cd_dir(char* _str, struct shell_state * dir)
{
	int i = 0;
	while (dir->pwd[i] != NULL)
		i++;

	if ((_str[3] == '.') && (_str[4] == '.') && (_str[5] == NULL))
	{
		while (((int)dir->pwd[i] != 47) && (i != 1))
			i--;
		if (i != 1)
			dir->pwd[i] = NULL;
		else
			printf("return impossible\n");
	}
	else
	{
		/* existence check */

		dir->pwd[i] = (char)47;
		i++;
		int j = 3;
		while (_str[j] != NULL)
		{
			dir->pwd[i] = _str[j];
			i++;
			j++;
		}
		dir->pwd[i] = NULL;
	}
	puts(dir->pwd);
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
