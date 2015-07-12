#include <stdio.h>
#include <deps/argtable3/argtable3.h>

/* Переменные в которых хранится информаци об аргументах командной строки */
struct arg_lit *help, *version;
struct arg_end *end;

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
	
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	return 0;
}