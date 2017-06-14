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
	uint64_t sec_cat;
	};

extern int get_mac_uname(struct usersec *, const char *);
extern int get_mac_uid(struct usersec *, uid_t uid);

