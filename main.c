#include <stdio.h>
#include "lib.h"


int main()
{
	char *uname;
	int sec_level;
	unsigned size = SIZE_INCREMENT;
	
	uname = (char *) malloc(size*sizeof(char *));
 
	printf("Insert user name and security level: \n");
	scanf("%s", uname);
	scanf("%d", &sec_level);

	struct usersec us;	
	get_user_mac(uname, sec_level, &us);

	return 0;
}

