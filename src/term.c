#include "inc/term.h"

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

/* Declaration of tty control structures */
struct termios old_tty, new_tty;

void term_set_driver() {
	tcgetattr( STDIN_FILENO, &old_tty);
	new_tty = old_tty;
	new_tty.c_lflag &= ~(ICANON|ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &new_tty);
}

void term_reset_driver() {
	tcsetattr( STDIN_FILENO, TCSANOW, &old_tty);
}

void term_read_line(int _argc, char** _argv) {
	char buff[1024];
	int argc=_argc;
	char* argv[255];
	int i = 0;
	int len=0;
	char ch;
	argv[0]=&buff[0];
	
	do {
		ch = getchar();
		putchar(ch);
		if (ch==' '){
			buff[len]='\0';
			i++;
			argv[i]=&buff[len+1];
		}
		else {buff[len]=ch;}
		len++;
	} while (ch!='\n');
	argv[i+1] = (char*)0;
}