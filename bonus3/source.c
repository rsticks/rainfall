#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char    flag[66] = {0};
	char    rest[65] = {0};
	FILE    *file = fopen("/home/user/end/.pass", "r");

   	if (argc != 2 || !file)
		return (1);
	fread(flag, 1, 66, file);
	flag[66] = 0;
	flag[atoi(argv[1])] = 0;
	fread(rest, 1, 65, file);
	fclose(file);
	if (strcmp(rest, argv[1]) == 0)
		execl("/bin/sh", "sh", NULL);
	else
		puts(rest);
}
