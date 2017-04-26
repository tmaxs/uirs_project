#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include <sys/types.h>
#include "lib.h"

#define FILE_DB "file_db.db"

static void string_parser(char *str, struct usersec *temp)
{	 
        char *token, *str1;
        char *saveptr;
        int j;

	str1 =  malloc(strlen(str) *sizeof(char *));
	
        for ( j = 0, str1 = str; ;j++, str1 = NULL)
        {
              	token = strtok_r(str1, "|", &saveptr);
				
                if (token == NULL)
                        break;	

                switch(j)
                {
                case 0: 
			temp->uname = malloc(strlen(token)*sizeof(char*));
			strcpy(temp->uname, token);
                        break;
              	case 1: temp->uid = atoi(token);
                        break;
            	case 2: 
			temp->sec_level = malloc(strlen(token)*sizeof(char*));				strcpy(temp->sec_level, token);
                        break;
                case 3: 
			temp->sec_cat = malloc(strlen(token)*sizeof(char*));
			strcpy(temp->sec_cat, token);
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

        for ( j = 0, str2 = str; ; j++, str2 = NULL)
        {
                token = strtok_r(str2, "[;]", &saveptr);
                if (token == NULL)
                      break;

                switch(j)
                {
                case 0: *min = atoi(token);
                        break;
                case 1: *max = atoi(token);
                        break;  
		}

        }

}


extern void *get_user_info (const char *uname, struct usersec *out)
{    
	
   
      FILE *file = fopen(FILE_DB, "r+t");
 	
	if (file != NULL)
	{
		char *str; 

		str = malloc(SIZE_INCREMENT *sizeof(char *));

		while (fgets(str, SIZE_INCREMENT, file) != NULL)
		{
			
			int min, max;
			char *str1;
			str1 = malloc(strlen(str) * sizeof(char *));
                     	int i=0;
                        while (i < strlen(str))
                        {
                                if (str[i]!='\n')
                                        str1[i] = str[i];
                                else
                                        str1[i] = '\0';
                        i++;
                        }
                     	strcpy(str, str1);
			
			struct usersec temp;
			string_parser(str, &temp);
			string_subparser(temp.sec_level, &min, &max);

			if (strcmp(temp.uname, uname) == 0 )
			{	
	  			out->uname = malloc(SIZE_INCREMENT *sizeof(char*));	
				strcpy(out->uname, temp.uname);
				out->uid = temp.uid;
				out->min = min;
				out->max = max;
				out->sec_cat = malloc(SIZE_INCREMENT *sizeof(char*));
				strcpy(out->sec_cat, temp.sec_cat);
			
				fclose(file);
				return;
			}
		}

	}
	fclose(file);
	//out = NULL;
	out->uid = -1;
}

