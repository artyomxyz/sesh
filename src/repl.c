#include "inc/repl.h"
#include "inc/term.h"
#include "inc/history.h"
#include "inc/help.h"
#include "inc/dir.h"
#include "inc/exec.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define KEY_BACKSPACE 8
#define KEY_DELETE 127
#define KEY_ARROWS 27
#define KEY_TAB 9
#define KEY_SC_UP 'A'
#define KEY_SC_DOWN 'B'
#define KEY_SC_RIGHT 'C'
#define KEY_SC_LEFT 'D'

char buff[1024];
char *cur;

void replace_buf(char *cmd_name){
	//char *cmd_cur=cmd_name;
	while((--cur)> buff) {
		write(STDOUT_FILENO, "\b \b", 3);
	}
	//cur++;
	while (*cmd_name!='\0'){
		write(STDOUT_FILENO,cmd_name,1);
		*(cur++)=*(cmd_name++);
	}
	*(cur++)='\0';		
	write(STDOUT_FILENO,buff,strlen(buff));
}

/* Description:
*	REPL = Read, Evaluate, Print, Loop	
*	It receives commands entered by the user and transmits them to the corresponding functions.  
*  Receives:
*	void
*  Returnes: 
*	void
*/

void repl () {
	char typecom[][8] = { "cd", "history", "help", "ls" };
	void(*arr_func[])(int, char**) = { dir_cmd, history_cmd, help_cmd, ls_cmd};
	
	while (1) {
		// Prompt
		char cwd[256];
		getcwd(cwd, 256);
		// printf("%s > ", cwd);
		write(STDOUT_FILENO, cwd, strlen(cwd));
		write(STDOUT_FILENO, " > ", 3);
		
		
		// Read
		cur = buff;
		char c[2];

		
		char *com_name=NULL;
		int h_count=0;

		while (read(STDIN_FILENO, &c, 1) != 0) {
			if (c[0] == '\n') {
				h_count=0;
				break;
			}
			switch(c[0]) {
				case KEY_BACKSPACE: 
				case KEY_DELETE:
					if (cur == buff) break;
					write(STDOUT_FILENO, "\b \b", 3);
					cur--;
					break;
				case KEY_ARROWS:
					read(STDIN_FILENO, &c, 2);
					if (c[0] == '['){
						switch(c[1]){
							case KEY_SC_UP:
								//write(STDOUT_FILENO, "up", 2);
								com_name=history_entry(h_count);
								replace_buf(com_name);
								//write(STDOUT_FILENO,com_name,strlen(com_name));	
								h_count++;
								break;
							case KEY_SC_DOWN:
								if (h_count<0) {
									write(STDOUT_FILENO,"fubar",5);	
								} else {
									com_name=history_entry(h_count);
									replace_buf(com_name);
									//write(STDOUT_FILENO,com_name,strlen(com_name));
									h_count--;
								}
								break;
							case KEY_SC_RIGHT:
								write(STDOUT_FILENO, "right", 5);
								break;
							case KEY_SC_LEFT:
								write(STDOUT_FILENO, "left", 4);
								break;
							     }
							}
					break;
				case KEY_TAB:
					write(STDOUT_FILENO, "	", 1);
					break;
					
				default: 
					write(STDOUT_FILENO, &c, 1);
					*(cur++) = c[0];
					break;
			}
		}
		*cur = '\0';
		char eol = '\n';
		write(STDOUT_FILENO, &eol, 1);
		

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
  		if (argc == 0) continue;

		if (strcmp(argv[0], "exit") == 0) {
			break;
		}

		int j;
		for (j = 0; j < 4; j++) {
			if (strcmp(argv[0], typecom[j]) == 0) {
				arr_func[j](argc, argv);
				break;
			}
		}

		if (j == 4) {
			exec_cmd(argc, argv);
		}
		// Loop		
	}
}
