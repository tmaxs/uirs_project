#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

#define FILE_DB "file_db.db"

extern void *get_user_info (char *uname, int sec_level, struct usersec *out)
{    
   
      FILE *file = fopen(FILE_DB, "r+t");
 
	if (file != NULL)
	{
		while (!feof(f))
		{
			struct usersec temp;
			char *str;
			int min, max;
			fgets(str, sizeof(str), f);
			string_parser(str, &temp);

			if (strcmp(temp.uname, uname) == 0 )
			{	
				string_subparser(temp.sec_level, &min, &max);				
				if ( min <= sec_level && max >=sec_level )
				{
				strcpy(out->uname, temp.uname);
				out->uid = temp.uid;
				strcpy(out->sec_level, temp.sec_level);
				strcpy(out->sec_cat, temp.sec_cat);
				}
			
			}
		}

	}
}
