#include "lib.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>
#include <sys/types.h>

#define PRIOR_CONFIG "prioritylib.conf"

static int load_lib_user_info (const char *uname, struct usersec *out)
{
	
	FILE *file = fopen(PRIOR_CONFIG,"r+t");
	
	if (file != NULL)
	{
             	char *libname;
		char *libn;
		char *error;
		unsigned size = SIZE_INCREMENT;
	
		libname = (char *) malloc(size * sizeof(char *));
		
            	while (fgets(libname,size,file)!= NULL)
         	{

			if(libname[0] == '#')
				continue;
			printf("%s", libname);
				
			libn = (char *) malloc(strlen(libname) * sizeof(char *));
			int i=0;
			while (i < strlen(libname))
			{
				if (libname[i]!='\n')
					libn[i] = libname[i];
				else 
					libn[i] = '\0';
			i++;
			}
			strcpy(libname, libn);		
			printf("|%s|\n", libname);
			printf ("%s\n", uname); 

			void *h = dlopen(libname, RTLD_LAZY);

				if(!h)
				{
					fputs (dlerror(), stderr);
					fprintf (stderr, "%s\n", error);
					exit(1);
				}
	
			typedef void *(*get_func)(const char *, struct usersec *);
			get_func lib_func = dlsym(h, "get_user_info");		
			
			if (lib_func != NULL)
                        {
                               
					struct usersec temp;					
					lib_func (uname, &temp);
					
					//printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:%s\n",temp.uname, temp.uid, temp.min, temp.max, temp.sec_cat);
					
					if( temp.uid == -1)
					{
							continue;
					}
					else
					{
					out->uname = malloc(size *sizeof(char*));	
				strcpy(out->uname, temp.uname);
				out->uid = temp.uid;
				out->min = temp.min;
				out->max = temp.max;
				out->sec_cat = malloc(size *sizeof(char*));
				strcpy(out->sec_cat, temp.sec_cat);
					fclose(file);
					return 0;
					}

					//printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:%s\n",temp.uname, temp.uid, temp.min, temp.max, temp.sec_cat);

			}		
					
						
			
					
		
		
		}
	}      
	fclose(file);
	return 1;             
}   

extern struct usersec get_user_mac(const char *uname)
{	
	if (uname == NULL)
	{
		printf("Error! Wrong uname\n");
		return;
        }

	struct usersec temp;
	if (load_lib_user_info(uname, &temp) != 0)                          
	{
		printf("Error!\n");
		return;
	}
	return temp;
	//printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:%s\n",temp.uname, temp.uid, temp.min, temp.max, temp.sec_cat);
}
