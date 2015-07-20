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

unsigned char buff[1024], buffcpy[1024];
unsigned char *cur;

void erase_char(){
	write(STDOUT_FILENO, "\b \b", 3);
	cur--;
	if (*cur >= 128) {
		cur--;
	}
}

void replace_buf(unsigned char *cmd_name) {
	//printf("[%d]\n", cur-buff);
	//char *cmd_cur=cmd_name;
	while (cur > buff) {
		erase_char();
	}
	while (*cmd_name != '\n'){
		*(cur++)=*(cmd_name++);
	}
	*(cur) = '\0';
	write(STDOUT_FILENO, buff, strlen(buff));
}

int parse_args(unsigned char* buff, char** argv) {
	int argc = 0;

	while (1) {
		if (buff == '\0') break;

		argv[argc++] = buff;

		// Search begin of next argument

		short notEscaped = 1;
		short slashEscaped = 0;

		while (*buff != '\0') {
			if (*buff == ' ' && notEscaped) break;
			if (*buff == '"' && !slashEscaped) notEscaped = !notEscaped;

			slashEscaped = 0;
			if (*buff == '\\') slashEscaped = 1;

			buff++;
		}

		if (*buff != '\0') {
			*buff = '\0';
			buff++;
		} else {
			break;
		}
	}

	//printf("%d\n", argc);

	argv[argc] = NULL;
	return argc;
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
	unsigned char typecom[][8] = { "cd", "history", "help", "ls" };
	void(*arr_func[])(int, char**) = { dir_cmd, history_cmd, help_cmd, ls_cmd};
	
	while (1) {
		// Prompt
		unsigned char cwd[256];
		getcwd(cwd, 256);
		// printf("%s > ", cwd);
		write(STDOUT_FILENO, cwd, strlen(cwd));
		write(STDOUT_FILENO, " > ", 3);		
		
		// Read
		cur = buff;
		unsigned char c[2];
		
		unsigned char *com_name = NULL;
		int h_count = 0;

		while (read(STDIN_FILENO, &c, 1) != 0) {
			if (c[0] == '\n') {
				h_count = 0;
				break;
			}
			switch(c[0]) {
				case KEY_BACKSPACE: 
				case KEY_DELETE:
					if (cur == buff) break;
					erase_char();		
					break;
					
				case KEY_ARROWS:
					read(STDIN_FILENO, &c, 2);
					if (c[0] == '['){
						switch(c[1]){
							case KEY_SC_UP:
								//write(STDOUT_FILENO, "up", 2);
								com_name = history_entry(h_count);
								if (com_name!=NULL){
									replace_buf(com_name);
									//write(STDOUT_FILENO,com_name,strlen(com_name));	
									h_count++;
								}
								break;
							case KEY_SC_DOWN:
								if (h_count<=0) {
									//write(STDOUT_FILENO,"fubar",5);	
									replace_buf("");
								} else {
									com_name = history_entry(h_count);
									if (com_name!=NULL){
										replace_buf(com_name);
										//write(STDOUT_FILENO,com_name,strlen(com_name));
									}
									h_count--;
								}
								break;
							case KEY_SC_RIGHT:
								//write(STDOUT_FILENO, "right", 5);
								break;
							case KEY_SC_LEFT:
								//write(STDOUT_FILENO, "left", 4);
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
		strcpy(buffcpy, buff);

		// Parse
		char* argv[256];
		int argc = parse_args(buff, argv);

		// Save entry in history
		
		if (argc > 0){
			history_save_cmd(buffcpy);
		}
		
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
