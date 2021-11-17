#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char    flag[66] = {0};
	char    rest[65] = {0};
	FILE    *file = fopen("/home/user/end/.pass", "r");

   	if ((!fs) || (argc != 2))
        return -1;

      fread(flag, 1, 66, fs);
      flag[atoi(argv[1])] = 0;

      fread(rest, 1, 65, fs);
      fclose(fs);

      if ( strcmp(flag, argv[1]) == 0)
        execl("/bin/sh","sh",0);
      else
        puts(rest);
}
