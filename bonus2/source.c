#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int     language = 0;

void    greetuser(char *str)
{
	char    buff[88];

	if (language == 1)
		memcpy(buff, "Hyvää päivää ", 17);
	else if (language == 2)
	    memcpy(buff, "Goedemiddag! ", 14);
    else
        memcpy(buff, "Hello ", 7);
	strcat(buff, str);
	puts(buff);
}

int     main(int argc, char **argv)
{
	char    first_name[40];
	char    second_name[32];
	char    *lang;

	if (argc != 3)
		return (1);
	memset(first_name, 0, 40);
	memset(second_name, 0, 32);
	strncpy(first_name, argv[1], 40);
	strncpy(second_name, argv[2], 32);
	lang = getenv("LANG");
	if (lang != 0)
	{
		if (memcmp(lang, "fi", 2) == 0)
			language = 1;
		else if (memcmp(lang, "nl", 2) == 0)
			language = 2;
	}
	greetuser(first_name);
}
