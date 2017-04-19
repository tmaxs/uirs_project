#include "lib.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>
#include <sys/types.h>

#define PRIOR_CONFIG "prioritylib.conf"


static int load_lib_user_info (const char *uname, uid_t uid, struct usersec *out)
{
	FILE *file = fopen(PRIOR_CONFIG,"r+t");
	
	if (file != NULL)
	{
		char *libn;
                char *libname;
		char *error;
		unsigned size = SIZE_INCREMENT;
		libn = (char *) malloc(size*sizeof(char *));
		
                while (!feof(file))
                {
                        libname = fgets(libn, sizeof(libn), file);
			if(libname[0] == '#')
				continue;
                        void *h = dlopen(libname, RTLD_LAZY);
			if(!h)
			{
				fputs (dlerror(), stderr);
				fprintf (stderr, "%s\n", error);
				exit(1);
			}
                        typedef struct usersec*(*get_func)(const char*, uid_t );
                        get_func my_func = dlsym(h, "get_user_info");
				
			if (my_func != NULL)
                        {
                               	if  (uname != 0)
                               	{
                                       	myfunc(uname, uid, &out);
					dlclose(h);
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
extern void get_user_mac(uid_t uid, const char *uname)
{
        if (uname == NULL)
        {
                printf("Error! Wrong uname\n");
                return;
        }
        if (uid == NULL)
        {
                printf("Error! Wrong value\n");
                return;
        } 

        struct usersec user;
	if (load_lib_user_info(uname, uid, &user) != 0)                          
	{
		printf("Error!\n");
		return;
	}
}

