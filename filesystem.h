#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>

// Открывает или создает файл файловой системы
FILE* открыть_или_создать_файл(const char* имя_файла);

// Просматривает содержимое файла внутри ФС
char* просмотреть_файл(const char* имя_фс, const char* имя_файла);

// Удаляет файл внутри ФС
int удалить_файл(const char* имя_фс, const char* имя_файла);

// Создает новый файл в ФС
int создать_новый_файл(const char* имя_фс, const char* имя_файла, const char* содержимое);

// Изменяет существующий файл
int изменить_файл(const char* имя_фс, const char* имя_файла, const char* новое_содержимое);

#endif
