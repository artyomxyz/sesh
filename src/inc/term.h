#pragma once

#define STDIN_FILENO 0

void term_set_driver();
void term_reset_driver();
void term_read_line(char* _str, char* _com);