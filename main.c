#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
//#include "lib.h"
#include "lib.c"

int main()
{
	char *uname;
	uid_t uid;
	unsigned size = SIZE_INCREMENT;
	
	uname = (char *) malloc(size*sizeof(char *));
 
	printf("Insert user name and security level: \n");
	scanf("%s", uname);
	scanf("%d", &uid);	
	get_user_mac(uname, uid);

	return 0;
}

