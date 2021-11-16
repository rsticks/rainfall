#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void p()
{
    char array[76];

    fflush(stdout);
    gets(array);
	if (((intptr_t)__builtin_return_address(0) & 0xb0000000) == 0xb0000000)
	{
		printf("(%p)\n", __builtin_return_address(0));
		_exit(1);
	}
	puts(array);
	strdup(array);
	return;
}

int main()
{
    p();
}
