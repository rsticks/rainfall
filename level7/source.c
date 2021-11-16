#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char    *c;

typedef struct {
    int     id;
    char    *value;
}       argument;

void m(void)
{
  printf("%s - %d\n", pass, time(0));
  return;
}

int     main(int argc, char **argv)
{
	FILE        *file;
	argument    *arg1;
	argument    *arg2;

	arg1 = (argument *)malloc(sizeof(argument));
	arg1->id = 1;
	arg1->value = (char *)malloc(8);
	arg2 = (argument *)malloc(sizeof(argument));
	arg2->id = 2;
	arg2->value = (char *)malloc(8);

	strcpy(arg1->value, argv[1]);
	strcpy(arg2->value, argv[2]);
	file = fopen("/home/user/level8/.pass", "r");
	fgets(c, 68, file);
	puts("~~");
}
