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