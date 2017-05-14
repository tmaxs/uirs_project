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
             	char *libname;
		char *libn;
	
		libname = malloc(sizeof(char));
	//	  printf ("%s\n", uname);

            	while (fgets(libname,SIZE_INCREMENT,file)!= NULL)
         	{

			if(libname[0] == '#')
				continue;
		//	printf("%s", libname);
				
			libn = malloc(sizeof(char));
			size_t i=0;
			while (i < strlen(libname))
			{
				if (libname[i]!='\n')
					libn[i] = libname[i];
				else 
					libn[i] = '\0';
			i++;
			}
			strcpy(libname, libn);	

		//	printf ("%s\n", uname); 
		//	printf("%d\n", uid);
			void *h = dlopen(libname, RTLD_LAZY);

				if (!h)
				{
					fprintf(stderr, "%s\n", dlerror());
					exit(EXIT_FAILURE);
				}
				dlerror();
				printf("Opened library |%s|.\n", libname);
	
			typedef void *(*get_func)(const char *, uid_t , struct usersec *);
			get_func lib_func = dlsym(h, "get_user_info");		
			printf("Function loaded.\n");
			if (lib_func != NULL)
                        {
                               
					struct usersec temp;					
					(*lib_func) (uname, uid, &temp);
					
					//printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:%s\n",temp.uname, temp.uid, temp.min, temp.max, temp.sec_cat);

					if( temp.uname== NULL)
					{
						printf("In the given library of the information on the user it is not found.\n");
						continue;
					}
					else
					{
					out->uname = malloc(sizeof(char));	
					strcpy(out->uname, temp.uname);
					out->uid = temp.uid;
					out->min = temp.min;
					out->max = temp.max;
					out->sec_cat = malloc(sizeof(char));
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
extern void *get_uname(struct usersec *out, const char *uname)
{	
	if (uname == NULL)
	{
		printf("Error! Wrong uname\n");
		exit (EXIT_SUCCESS);

        }
	uid_t uid;
	struct usersec temp;
	if (load_lib_user_info(uname,uid, &temp) != 0)                          
	{
		printf("Error!\n");
		exit (EXIT_SUCCESS);	
	
	}
	
	/*char *name = malloc(sizeof(char));
	name = &temp.uname;
	uid_t uid = &temp.uid;
	int min = &temp.min;
	int max = &temp.max;
	char *sec_cat = malloc(sizeof(char));
	sec_cat = &temp.sec_cat;*/
	
	out->uname = malloc(sizeof(char));
	strcpy(out->uname, temp.uname);
	out->uid = temp.uid;
	out->min = temp.min;
	out->max = temp.max;
	out->sec_cat = malloc(sizeof(char));
	strcpy(out->sec_cat, temp.sec_cat);
	/*printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:%s\n",*name, *uid, *min, *max, *sec_cat);*/
	return out;

	//getch(out);
}
extern void *get_uid(struct usersec *out, uid_t uid)
{
//	printf("%d\n", uid);
	if( uid == 0)
	{
		printf("Error! Wrong uid\n");
		exit (EXIT_SUCCESS);
	
	}
	char *uname;
	struct usersec temp;
        if (load_lib_user_info(uname, uid, &temp) != 0)
        {
                printf("Error!\n");
                exit (EXIT_SUCCESS);

        }
	out->uname = malloc(sizeof(char));
        strcpy(out->uname, temp.uname);
        out->uid = temp.uid;
        out->min = temp.min;
        out->max = temp.max;
        out->sec_cat = malloc(sizeof(char));
        strcpy(out->sec_cat, temp.sec_cat);
	return out;
}
