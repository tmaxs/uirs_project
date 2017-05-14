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

	str1 =  malloc(sizeof(char));
	
        for ( j = 0, str1 = str; ;j++, str1 = NULL)
        {
              	token = strtok_r(str1, "|", &saveptr);
				
                if (token == NULL)
                        break;	

                switch(j)
                {
                case 0: 
			temp->uname = malloc(sizeof(char));
			strcpy(temp->uname, token);
                        break;
              	case 1: temp->uid = atoi(token);
                        break;
            	case 2: 
			temp->sec_level = malloc(sizeof(char));				strcpy(temp->sec_level, token);
                        break;
                case 3: 
			temp->sec_cat = malloc(sizeof(char));
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


extern void *get_user_info (const char *uname, uid_t uid, struct usersec *out)
{    
	
   
      FILE *file = fopen(FILE_DB, "r+t");
 	
	if (file != NULL)
	{
		char *str; 

		str = malloc(sizeof(char));

		while (fgets(str, SIZE_INCREMENT, file) != NULL)
		{
			
			int min, max;
			char *str1;
			str1 = malloc(strlen(str) * sizeof(char *));
                     	size_t i=0;
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

			if (strcmp(temp.uname, uname) == 0 || temp.uid == uid )
			{	
	  			out->uname = malloc(sizeof(char));	
				strcpy(out->uname, temp.uname);
				out->uid = temp.uid;
				out->min = min;
				out->max = max;
				out->sec_cat = malloc(sizeof(char));
				strcpy(out->sec_cat, temp.sec_cat);
			
				fclose(file);
				return out;
			} 
		}
		free(str);
	}
	
	fclose(file);
	//out = NULL;
	out->uname = NULL ;
	return NULL;
}

