#pragma once

void history_init();
void history_cmd(int argc, char** argv);
void history_save_cmd(char* _com);
char* history_entry(int i);