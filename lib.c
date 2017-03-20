#include "lib.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>
#include <sys/types.h>

#define PRIOR_CONFIG "prioritylib.conf"


static int load_lib_user_info (const char *uname, int sec_level, struct usersec *out)
{
	FILE *file = fopen(CONFIG,"r+t");
	
	if (file != NULL)
	{
		char *libn;
                char *libname;
		unsigned size = SIZE_INCREMENT;
		libn = (char *) malloc(size*sizeof(char *));
		
                while (!feof(file))
                {
                        libname = fgets(libn, sizeof(libn), file);
			if(libname[0] == '#')
				continue;
                        void *h = dlopen(libname, RTLD_LAZY);
			if(h != NULL )
			{	
                        	typedef struct usersec*(*get_func)(const char*, int );
                        	get_func my_func = dlsym(h, "get_user_info");
				
				if (my_func != NULL)
                        	{
                                	if  (uname != 0)
                                	{
                                        	myfunc(uname, sec_level, &out);
						dlclose(h);
                                	}
                                }
                        }
		}
		if(out != NULL)
		{
			fclose(file);
			return 0;
		}
	}      
	fclose(file);
	return 1;             
}
static void string_parser(char *str, struct usersec *temp)
{

        char *str1, *token;
        char *saveptr;
        int j;

        for ( j = 0, str1 = str; ;j++, str1 = NULL)
        {
                token = strtok_r(str1, "|", &saveptr);
                if (token == NULL)
                        break;

                switch(j)
                {
                case 0: strcpy(temp->uname, token);
                        break;
                case 1: temp->uid = atoi(token);
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
        char  *str1, *token;
        char *saveptr;


        for (int j = 0, str1 = str; ; j++, str1 = NULL)
        {
                token = strtok_r(str1, "[;]", &saveptr);
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
extern void get_user_mac(const char *uname, int sec_level)
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
}

