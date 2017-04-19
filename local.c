#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include <sys/types.h>

#define FILE_DB "file_db.db"

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

			if (strcmp(temp.uname, uname) == 0 )
			{	
				string_subparser(temp.sec_level, &min, &max);	

				{
				strcpy(out->uname, temp.uname);
				out->uid = temp.uid;
				out->min = temp.min;
				out->max = temp.max;
				out->sec_cat = temp.sec_cat;
				}
			
			}
		}

	}
}
