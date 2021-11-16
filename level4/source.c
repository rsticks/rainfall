#include <stdio.h>
#include <stdlib.h>

int     m;

int		p(char *buffer)
{
	printf(buffer);
	return (0);
}
void n()
{
    char buf[520];

    fgets(buf, 512, stdin);
    p(buf);
    if (m == 16930116)
    	system("/bin/cat /home/user/level5/.pass");
    return (0);
}

int     main(void)
{
    n();
}
