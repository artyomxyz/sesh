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

void term_read_line(char* _str, char* _com) {

	int i = 0;	
	
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
}