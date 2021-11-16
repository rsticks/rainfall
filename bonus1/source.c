#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char    buffer[40];
	int     i;

	i = atoi(argv[1]);
	if (i <= 9)
	{
        memcpy(buffer, argv[2], i * 4);
        if (i == 0x574F4C46)
            execl("/bin/sh", "sh", NULL);
        return (0);
	}
}
