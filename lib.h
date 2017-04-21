#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>

#define SIZE_INCREMENT 256

struct usersec
	{
	char *uname, *sec_level;
	uid_t uid;
	int min, max;
	char *sec_cat;
	};

extern void get_user_mac(const char *uname, uid_t uid);
extern void *get_user_info(char *uname, uid_t uid, struct usersec *out);
static void string_parser(char *str, struct usersec *temp);
static void string_subparser(char *str, int *min, int *max);
