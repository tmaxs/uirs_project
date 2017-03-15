#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>



 extern struct usersec *get_user_info (char *uname, int sec_level, struct usersec *out)
  {    
   
      FILE *f = fopen("liblocal.so" , "r+t");
 
	if (f != 0)
	{
		while (!feof(f))
		{
			struct usersec temp;
			char str[80];
			fgets(str, 80, f);
			stringParser(str, &temp);

			if (strcmp(temp.uname, uname) == 0 )
				if (temp.sec_level == sec_level)
			{
				strcpy(out->uname, temp.uname);
				out->uid = temp.uid;
				out->sec_level = temp.sec_level;
				strcpy(out->sec_cat, temp.sec_cat);

			}
		}
	}
   }
