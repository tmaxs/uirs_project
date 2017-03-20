#include <stdint.h>
#include <sys/types.h>

#define SIZE_INCREMENT 100

struct usersec
	{
	char *uname;
	uid_t uid;
	int sec_level;
	uint64_t sec_cat;
	};

extern void get_user_mac(const char *uname, int sec_level);

