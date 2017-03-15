#include <stdint.h>
#include <sys/types.h>

struct usersec
	{
	char uname[80];
	uid_t uid;
	int sec_level;
	uint64_t sec_cat;
	};

extern struct usersec get_user_mac(const char *uname, int sec_level);

