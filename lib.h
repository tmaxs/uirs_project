#include <stdint.h>
#include <sys/types.h>

#define SIZE_INCREMENT 100

struct usersec
	{
	char *uname, *sec_level;
	uid_t uid;
	int min, max;
	uint64_t sec_cat;
	};

extern void get_user_mac(const char *uname, int sec_level);

