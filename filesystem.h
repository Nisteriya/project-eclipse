#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>

// Открывает или создает файл файловой системы
FILE* create_open_file(const char* filename);

// Просматривает содержимое файла внутри ФС
char* view_file(const char* имя_фс, const char* filename);

// Удаляет файл внутри ФС
char* delete_file(const char* filename);

// Создает новый файл в ФС
char* add_file(const char* main_filename);

// Изменяет существующий файл
char* modify_file(const char* filename);;

#endif
