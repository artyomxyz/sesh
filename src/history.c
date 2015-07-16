#include "inc/history.h"

#include <stdio.h>

FILE* history_fd;

void history_init()
{
	const char * ghp(const char * ot)
	{
		static char buff[256];
		strcpy(buff, getenv("HOME"));
		strcat(buff, ot);
		return buff;
	}
	history_fd=fopen("ghp('.sesh_history')","a+");
}

void history_cmd(char* _str, char* _com)
{
	char str[50];
	history_init();
	if (history_fd==NULL)
	{
		puts("History is empty.\n");
	}
	else
	{
		printf("This is history:\n");
		while (fgets(str,50,history_fd)!=NULL)
		{
			printf("%s",str);
		}
	}
	fclose(history_fd);
}
void history_save_cmd(char* _com)
{
	history_init();
	if (history_fd==NULL)
	{
		puts("Problems!\n");
	}
	fputs(_com,history_fd);
	fputs("\n",history_fd);
	fclose(history_fd);
}
