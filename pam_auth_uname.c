#include <sys/types.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "lib.h"
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#define PAM_SM_AUTH
	int i, rv, sec_level;
	uint64_t sec_cat;
	const char *user;
	struct pam_conv *conv; 
	struct pam_message msg;
	struct pam_message *(msgp[1]);
	struct pam_response *resp;
	struct usersec temp;

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	rv=pam_get_user(pamh, &user, "Uname: ");

	printf("Founding user...\n");

	if (rv!=PAM_SUCCESS)
	{
		pam_syslog(pamh, LOG_ERR, "pam_get_user() failed %s", pam_strerror(pamh, rv));
		rv=PAM_USER_UNKNOWN;
		goto out;
	} 
	if (get_mac_uname(&temp, user) != 0)
	{
		pam_syslog(pamh, LOG_ERR, "User not found in privileges database %s", user);
		rv=PAM_USER_UNKNOWN;
		goto out;
	}

	printf("User founded: %s\n", user);
	printf("Enter security level: %d\n");
	scanf("%d\n", sec_level);
	if (!(temp.min <= sec_level <= temp.max))
	{
		pam_syslog(pamh, LOG_ERR, "Security level not available!\n" );
		rv = PAM_AUTHINFO_UNAVAIL;
		goto out;
	
	}
	else 
	{
		return PAM_AUTH_ERR;
	}

	printf("Security category: %d\n");
	scanf("%d\n", sec_cat);
	if (!(sec_cat = temp.sec_cat))
	{
		pam_syslog(pamh, LOG_ERR, "Security category not available!\n" );
                rv = PAM_AUTHINFO_UNAVAIL;
                goto out;
	}
	else
	{
		return PAM_AUTH_ERR;
	}
	printf("User auth.\n");
	rv=PAM_SUCCESS;
	goto out;
out:
	return rv;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t * pamh, int flags,int argc, const char **argv)
{
        int rv;
        rv = PAM_SUCCESS;
        return rv;
}

int pam_acct_mgmt(pam_handle_t *pamh, int flags)
{
	return PAM_SUCCESS ;
}
int pam_open_session(pam_handle_t *pamh, int flags)
{
	return PAM_SUCCESS ;
}

int pam_close_session(pam_handle_t *pamh, int flags)
{
	return PAM_SUCCESS ;
}
#ifdef PAM_STATIC
struct pam_module _pam_unix_auth_modstruct = {
    "pam_test",
    pam_sm_authenticate,
    pam_sm_setcred,
    NULL,
    NULL,
    NULL,
    NULL,
};
#endif

