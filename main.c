#include <stdio.h>
#include "lib.h"


int main()
{
	char uname[80];
	int sec_level;

	printf("Insert user name and security level: \n");
	scanf("%s", uname);
	scanf("%d", &sec_level);

	get_user_mac(uname, sec_level);

	return 0;
}

