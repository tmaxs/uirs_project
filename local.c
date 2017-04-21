#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include <sys/types.h>

#define FILE_DB "file_db.db"

static void string_parser(char *str, struct usersec *temp)
{

        char *str1, *token;
        char *saveptr;
        int j;
	unsigned size = SIZE_INCREMENT;

     //   token = (char *) malloc(sizeof(char *));

        for ( j = 0, str1 = str; ;j++, str1 = NULL)
        {
                token = strtok_r(str1, "|", &saveptr);
                if (token == NULL)
                        break;

                switch(j)
                {
                case 0: strcpy(temp->uname, token);
                        break;
                case 1: temp->uid = token;
                        break;
                case 2: strcpy(temp->sec_level, token);
                        break;
                case 3: strcpy(temp->sec_cat, token);
                        break;
                }
        }

}

static void string_subparser(char *str, int *min, int *max)
{
        char *str2;
        char *token;
        char *saveptr;
        int j;

       // token = (char *) malloc(sizeof(char *));

        for ( j = 0, str2 = str; ; j++, str2 = NULL)
        {
                token = strtok_r(str2, "[;]", &saveptr);
                if (token == NULL)
                      break;

                switch(j)
                {
                case 0: min = atoi(token);
                        break;
                case 1: max = atoi(token);
                        break;
                }

        }

}


extern void *get_user_info (char *uname, uid_t uid, struct usersec *out)
{    
   
      FILE *file = fopen(FILE_DB, "r+t");
 
	if (file != NULL)
	{
		while (!feof(file))
		{
			struct usersec temp;
			char *str;
			int min, max;
			fgets(str, sizeof(str), file);
			string_parser(str, &temp);

			str = (char *) malloc(sizeof(char *));

			if (strcmp(temp.uname, uname) == 0 )
			{	
				string_subparser(temp.sec_level, &min, &max);	

				{
				strcpy(out->uname, temp.uname);
				out->uid = temp.uid;
				out->min = temp.min;
				out->max = temp.max;
				strcpy(out->sec_cat, temp.sec_cat);
				}
			
			}
		}

	}
}
