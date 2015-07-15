#include "inc/history.h"

#include <stdio.h>

void history_cmd(char* _str, char* _com)
{
	char str[50];
					
	const char * ghp(const char * ot)
	{
		static char buff[256];
		strcpy(buff, getenv("HOME"));
		strcat(buff, ot);
		return buff;
	}
					
	FILE *pfile;
	pfile=fopen("ghp('.sesh_history')","r");
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
				
	        const char * ghp(const char * ot)
        {
                static char buff[256];
                strcpy(buff, getenv("HOME"));
                strcat(buff, ot);
                return buff;
        }
        			
	pfile=fopen("ghp('.sesh_history')","a");
	if (pfile==NULL)
	{
		puts("Problems!\n");
	}
	fputs(_com,pfile);
	fputs("\n",pfile);
	fclose(pfile);
}
