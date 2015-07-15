#include "inc/repl.h"
#include "inc/term.h"
#include "inc/history.h"
#include "inc/help.h"
#include "inc/cmd_cd.h"
#include "inc/exec.h"
#include "inc/ls.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void repl () {
	char typecom[][8] = { "cd", "history", "help", "ls", "exit" };
	void(*arr_func[])(char*, char*) = { cmd_cd, history_cmd, cmd_help, ls_cmd };

	int i = 0;
	char com[80], str[80];
	
	char dir[256];
	do {
		getcwd(dir, 256);
		printf("%s > ", dir);

		term_read_line(str, com);
		history_save_cmd(str);

		for (i = 0; i < 5; i++) {
			if (strcmp(com, typecom[i]) == 0) {
				arr_func[i](str, com);
				break;
			}
		}

		if (i == 5) {
			cmd_exec(str, com);
		}
		
		
	} while (strcmp(com, typecom[3]) != 0);
}