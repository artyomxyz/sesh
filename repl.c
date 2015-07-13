#include <stdio.h>
#include <deps/argtable3/argtable3.h>
#include <fcntl.h>
#include <termios.h>

/* Объявление двух переменных для хранения управляющих структур */
struct termios _savetty;
struct termios _tty;
/* Переменные в которых хранится информаци об аргументах командной строки */
struct arg_lit *help, *version;
struct arg_end *end;

//protipes
void change_driver(struct termios* savetty,struct termios* tty);
void read_str(char* _str, char* _com);
void cmd_cd(char* _str, char* _com);
void cmd_his(char* _str, char* _com);
void cmd_help(char* _str, char* _com);
void cmd_exep(char* _str, char* _com);
int main(int argc, char *argv[])
{
	/* Таблица аргументов */
	void *argtable[] = {
		help    = arg_litn("h", "help", 0, 1, "Display this help and exit"),
		version = arg_litn("v", "version", 0, 1, "Display version info and exit"),
		end     = arg_end(20),
	};

	/* Название нашей программы */
	char progname[] = "sesh";
	char progversion[] = "0.0.0";

	/* Количество ошибок про разборе аргументов */
	int nerrors = arg_parse(argc, argv, argtable);

	/* В случае если была вызвана помощь мы забиваем на ошибки */
	if (help->count > 0) {
		printf("Usage: %s", progname);
		arg_print_syntax(stdout, argtable, "\n");
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 0;
	}

	/* Если при разборе аргументов произошли ошибки */
	if (nerrors > 0) {
		/* Печатаем информацию об ошибке */
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

	change_driver(struct termios* _savetty,struct termios* _tty);
	
//main lex
	char typecom[][8] = { "cd", "history", "help", "exep", "exit" };
	void(*arr_func[])(char*, char*) = { cmd_cd, cmd_his, cmd_help, cmd_exep };

	int i = 0;
	char com[80], str[80];


	do
	{
		read_str(str, com);
		for (i = 0; i < 4; i++)
		{
			if (strcmp(com, typecom[i]) == 0)
				arr_func[i](str, com);
		}
		i = 0;
	} while (strcmp(com, typecom[4]) != 0);

	/* exit */

	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;
}

change_driver(struct termios* savetty,struct termios* tty)
{
	if ( !isatty(0) ) { /*Проверка: стандартный ввод - терминал?*/
 	 fprintf (stderr, "stdin not terminal\n");
 	 exit (1); /* Ст. ввод был перенаправлен на файл, канал и т.п. */
 	 };

	tcgetattr (0, &tty);
	savetty = tty; /* Сохранить упр. информацию канонического режима */
	tty.c_lflag &= ~(ICANON|ECHO|ISIG);
	tty.c_cc[VMIN] = 1;
	tcsetattr (0, TCSAFLUSH, &tty);
}

//funct	
	void read_str(char* _str, char* _com)
{

	int i = 0;

	do
	{
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

void cmd_cd(char* _str, char* _com) { printf("This is cd\n"); };
void cmd_his(char* _str, char* _com) { printf("This is hystory\n"); };
void cmd_help(char* _str, char* _com) { printf("This is help\n"); };
void cmd_exep(char* _str, char* _com) { printf("This is exep\n"); };