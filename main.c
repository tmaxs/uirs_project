#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "lib.h"

int main()
{
	char *uname;
	uid_t uid;
      
        uname = malloc(SIZE_INCREMENT * sizeof(char *));

        printf("Insert user name:\n");
        scanf("%s", uname);
        printf("User name: %s\n", uname);

        struct usersec temp;

      	temp = get_user_mac(uname);
        printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:%s\n",temp.uname, temp.uid, temp.min, temp.max, temp.sec_cat);
        return 0;

}
