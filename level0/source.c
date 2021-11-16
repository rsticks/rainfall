#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char *s[2];
    int uid;
    int gid;

    if (atoi(argv[1]) == 423)
    {
        s[0] = strdup("/bin/sh");
        s[1] = 0;
        gid = getegid();
        uid = geteuid();

        setresgid(getegid(), getegid(), getegid());
        setresuid(geteuid(), geteuid(), geteuid());
        execv("/bin/sh", args);
    }
    fwrite("No !\n", 1, 5, stderr);
    return (0);
}
