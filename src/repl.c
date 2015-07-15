#include "inc/repl.h"
#include "inc/term.h"
#include "inc/history.h"
#include "inc/help.h"
#include "inc/dir.h"
#include "inc/exec.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void repl () {
	char typecom[][8] = { "cd", "history", "help" };
	void(*arr_func[])(int, char**) = { dir_cmd, history_cmd, help_cmd};
	
	while (1) {
		// Prompt
		char cwd[256];
		getcwd(cwd, 256);
		printf("%s > ", cwd);
		
		
		// Read
		char buff[1024];
		char *cur = buff;
		char c;

		while ( (c=getchar()) != '\n' ) {
			putchar(c);
			*(cur++) = c;
		}
		*cur = '\0';
		putchar('\n');

		// Save entry in history
		history_save_cmd(buff);

		// Parse

		int argc = 0;
		char* argv[256];


		char* pch = strtok(buff, " ");
  		while (pch != NULL) {
  			argv[argc++] = pch;
  			pch = strtok(NULL, " ");
  		}
  		argv[argc] = NULL;

		// Route
		if (strcmp(argv[0], "exit") == 0) {
			break;
		}

		int j;
		for (j = 0; j < 3; j++) {
			if (strcmp(argv[0], typecom[j]) == 0) {
				arr_func[j](argc, argv);
				break;
			}
		}

		if (j == 3) {
			exec_cmd(argc, argv);
		}
		// Loop		
	}
}