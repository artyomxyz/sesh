#include "inc/history.h"

#include <stdio.h>

void history_cmd(int argc, char** argv)
{
	char str[50];
	FILE *pfile;
	pfile=fopen(".sesh_history","r");
	if (pfile==NULL)
	{
		puts("History is empty.\n");
	}
	else
	{
		printf("This is history:\n");
		while (fgets(str,50,pfile)!=NULL)
 		{
			printf("%s",str);
		}
	}
	fclose(pfile);
}
void history_save_cmd(char* _com)
{
	FILE *pfile;
	pfile=fopen(".sesh_history","a");
	if (pfile==NULL)
	{
		puts("Problems!\n");
	}
	fputs(_com,pfile);
	fputs("\n",pfile);
	fclose(pfile);
}