# Простой мессенджер на C++

## О проекте
Данный проект осуществляет простую передечу данных по протоколу TCP/IP

Клиент и сервер написаны на основе фреймворка [Qt](https://www.qt.io/)


## Как скачать и запустить проект
1. Создайте папку с проектом и зайдите в него
> mkdir Project && cd Project

2. Склонируйте туда репизиторий с **GitHub**
> git clone https://github.com/Beibala05/Messanger.git

3. Создайте папку build
> mkdir build

4. Соберите проект с помощью **CMake**
> cmake -B build 

5. Соберите полученный **MakeFile**
> make

## Макроподстановки

Макрос ```DEBUG_OFF``` встречается в заголовке **server.h**, нужен для того чтобы отключать сообщения от сервера в терминал

### server.h
```C++
#define DEBUG_OFF // 11 строка
```