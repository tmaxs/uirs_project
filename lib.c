#include "lib.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>
#include <sys/types.h>


static int load_lib_user_info (const char *uname, int sec_level, struct usersec *out)
{
	FILE *file = fopen("prioritylib.conf","r+t");
	
	if (file != 0)
	{
		char libn[80];
                char *libname;
                while (!feof(file))
                {
                        libname = fgets(libn, sizeof(libn), file);

                        void *h = dlopen(libname, RTLD_LAZY);
                        typedef struct usersec*(*get_func)(char*, int );
                        get_func my_func = dlsym(h, "get_user_info");

                        if (my_func == NULL)
                        {
                                if  (uname != 0)
                                {
                                        struct usersec*data = myfunc(uname, sec_level);
                                        dlclose(h);
                                        fclose(file);
                                }
                                else
                                {
                                        dlclose(h);
                                }
				return 0;
			}              
			else 
				return 1;
		}
	}                    
}
static void stringParser(char *str, int sec_level, struct usersec *temp)
{
	int value = 0, j = 0;
	char temp_str[80];
        int i = 0;

	while ( i < strlen(str))
	{
		if (str[i] == '|' || i == strlen(str)-1)
		{
			temp_str[j] = '\0';
			
			switch (value)
			{
			case 0: strcpy(temp->uname, temp_str);
				break;
			case 1: temp->uid = atoi(temp_str);
				break;
			case 2: {
				int k = 0, q = 0, min, max;
				char temp_tstr[80];
				while ( k < strlen(temp_str))
				{
					if (temp_str[k] == ';')
					{
						temp_tstr[q] = '\0';
						min = atoi(temp_tstr);

						strcpy(temp_tstr, "");
					}
                                    	if ( k == strlen(temp_str)-1)
					{
						temp_tstr[q] = '\0';
						max = atoi(temp_tstr);

						strcpy(temp_tstr, "");
					}
					
					temp_tstr[q++] = temp_str[k];
					k++;  
				} 

				if(min <= sec_level && max >= sec_level)
					temp->sec_level = sec_level;
				break;
                                }
			case 3: strcpy(temp->sec_cat, temp_str);
				break;
			}

			strcpy(temp_str, "");
			j = 0;
			value++;

		}
		else
			temp_str[j++] = str[i];
                i++;  
 
	}
}

extern struct usersec get_user_mac(const char *uname, int sec_level)
{
        if (uname == NULL)
        {
                printf("Error! Wrong uname\n");
                return;
        }
        if (sec_level < 0 || sec_level > 3)
        {
                printf("Error! Wrong value\n");
                return;
        } 

        struct usersec user;
	if (load_lib_user_info(uname, sec_level, &user) != 0)                          
	{
		printf("Error!\n");
		return;
	}
       return user;
}
