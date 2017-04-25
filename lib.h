#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>

#define SIZE_INCREMENT 256

struct usersec
	{
	char *uname;
	char *sec_level;
	uid_t uid;
	int min, max;
	char *sec_cat;
	};

extern struct usersec get_user_mac(const char *);
//extern void *get_user_info(char *uname, struct usersec *out);

