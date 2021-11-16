#include <stdio.h>
#include <stdlib.h>

void    o()
{
	system("/bin/sh");
	_exit(1);
}
void    n(void)
{
	char buf[512];

	fgets(buf, 512, stdin);
	printf(buf);
	exit(1);
}

int     main()
{
	n();
}
