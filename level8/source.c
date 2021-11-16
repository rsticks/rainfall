#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char    *service;
char    *auth;

int     main()
{
	char buf[128];

	do
	{
		printf("%p, %p \n", auth, service);
		char *res = fgets(buf, 128, stdin);
		if (!res)
			break;
		if (strncmp(buf, "auth ", 5) == 0)
		{
			auth = (char *)malloc(4);
			if (strlen(buf + 5) - 1 < 30)
				strcpy(auth, buf + 5);
		}
		else if (strncmp(buf, "reset", 5) == 0)
			free(auth);
		else if (strncmp(buf, "service", 6) == 0)
			service = strdup(buf + 7);
		else if (strncmp(buf, "login", 5) == 0)
		{
			if (auth[32])
				system("/bin/sh");
			else
				fwrite(&"Password:\n", 10, 1, stdout);
		}
	}
	while (true);
    return 0;
}
