#include "inc/dir.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

	char* array[256];
	char buff[8192];

char** ls_cmd(int argc, char** argv) 
{
	struct dirent *entry;
	char name_dir[256];

	int Wcounter = 0;
	int Scounter = 0;
	
	getcwd(name_dir, 256);
    	DIR *dir=opendir(name_dir);
   
   	if (!dir)
        	printf("Sorry, can' t do ls.");

   	while ( (entry = readdir(dir)) != NULL)
	{	
		int i = 0;
		int a = 0;	
		while((argv[1][i] != NULL))
		{
			if(entry->d_name[i] != argv[1][i])
			{
				a = 1;
				break;
			}
			if(argv[1][i] == NULL)
				break;
			if(entry->d_name[i] == NULL)
 			{
				a = 1;
				break;
			}
			i++;
		}
		if (a == 0)
		{
			Wcounter++;
			array[Wcounter] = buff+Scounter;
			i = 0;
			while(entry->d_name[i]!=0)
			{
				buff[Scounter] = entry->d_name[i];
				printf("%c\n",buff[Scounter]);
				Scounter++;
				i++;
			}
			buff[Scounter]=NULL;
			Scounter++;
		}
 	} 
	closedir(dir);

	return (array);

}