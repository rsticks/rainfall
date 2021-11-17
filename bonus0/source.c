#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void    p(char *str, char *sep)
{
	char buf[4096];

	puts(sep);
	read(0, buf, 4096);
    *strchr(buff, '\n') = 0;

    strncpy(s, buff, 20);
    return;
}

void    pp(char *s)
{
	char buf1[20];
	char buf2[20];

	p(buf1, " - ");
	p(buf2, " - ");
    strcpy(s, str1);
	s[strlen(s)] = 32;

    strcat(s, str2);
    return;
}

int     main(int argc, char **argv)
{
	char buf[54];

	pp(buf);
	puts(buf);
	return (0);
}
