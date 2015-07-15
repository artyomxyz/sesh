#include "inc/repl.h"
#include "inc/term.h"
#include "inc/history.h"
#include "inc/help.h"
#include "inc/cmd_cd.h"
#include "inc/exec.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void repl () {
	char typecom[][8] = { "cd", "history", "help", "exit" };
	void(*arr_func[])(int, char**) = { cmd_cd, history_cmd, cmd_help};
	
	char* argv[255];
	char dir[256];
	char buff[1024];
	int i = 0;
	int j = 0;
	int argc=1;
	int len=0;
	char ch;
	
	do {
		getcwd(dir, 256);
		printf("%s > ", dir);
		
		argc=1;	
		i = 0;
		len=0;
		argv[0]=&buff[0];
	
		do {
			ch = getchar();
			putchar(ch);
			if (ch=='\n') break;
			if (ch==' '){
				buff[len]='\0';
				i++;
				argv[i]=&buff[len+1];
				argc++;
			}
			else {buff[len]=ch;}
			len++;
		} while (0==0);
		argv[i+1] = (char*)0;
		buff[len]='\0';
		
		//history_save_cmd(str);
		for (j = 0; j < 4; j++) {
			if (strcmp(argv[0], typecom[j]) == 0) {
				arr_func[j](argc, argv);
				break;
			}
		}

		if (j == 4) {
			sleep(0.5);
			cmd_exec(argc, argv);
		}
		
		
	} while (strcmp(argv[0], typecom[3]) != 0) ;
}