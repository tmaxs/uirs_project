#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "lib.h"

int main()
{
	char *uname;
	uid_t uid;
	unsigned size = SIZE_INCREMENT;
	
	uname = (char *) malloc(size * sizeof(char *));
 
	printf("Insert user name and user id: \n");
	scanf("%s", uname);
	printf("User name: %s\n", uname);
	scanf("%d", &uid);
	printf("Uid: %d\n", uid );	
	get_user_mac(uname, uid);

	return 0;
}

