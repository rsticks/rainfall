#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void    p(char *str, char *sep)
{
	char buf[4096];

	puts(sep);
	read(0, buf, 4096);
	*strchr(buf, '\n') = 0;
	strncpy(str, buf, 20);
}

void    pp(char *buf)
{
	char buf1[20];
	char buf2[20];

	p(buf1, " - ");
	p(buf2, " - ");
	strcpy(buf, buf1);
	buf[strlen(buf1)] = ' ';
	strcat(buf, buf2);
}

int     main(int argc, char **argv)
{
	char buf[54];

	pp(buf);
	puts(buf);
	return (0);
}
