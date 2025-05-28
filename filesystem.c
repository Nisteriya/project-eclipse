#include <stdio.h>
#include <string.h>
#include "filesystem.h"

#define MAX_SIZE 1024

FILE* create_open_file(const char* filename) {
    FILE* fp = fopen(filename, "a+");
    if (fp == NULL) {
        perror("Ошибка при открытии файла");
        return NULL;
    }
    return fp;
}

char* view_file(const char* filename) {
    
    FILE* fs_file = fopen(filename, "r");

    char line[MAX_SIZE];
    int found = 0;
    char content[MAX_SIZE]; 
    content[0] = '\0';

    while (fgets(line, sizeof(line), fs_file)) {
        // Удаляем символ новой строки
        int i = 0;
        while (line[i] != '\n' && line[i] != '\0') i++;
        line[i] = '\0';

        if (!found) {
            int match = 1;
            for (i = 0; filename[i] != '\0' && line[i] != '\0'; i++) {
                if (filename[i] != line[i]) {
                    match = 0;
                    break;
                }
            }
            if (match && filename[i] == '\0' && line[i] == '\0') {
                found = 1;
            }
        } else {
            if (line[0] == '/') break;

            if (content[0] != '\0') {
                strcat(content, "\n");
            }
            strcat(content, line);
        }
    }

    return content;
}

char* delete_file(const char* filename) {
    if (remove(filename) == 0) return "ФАЙЛ УДАЛЕН";
    
    return "ОШИБКА";
}

char* add_file(const char* main_filename) {
    char filename[1024];
    printf("Введите название файла из ФС\n");
    scanf("%s", filename);
    
    
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return "ERROR\n";
    }
    fclose(fp);
    
    fp = fopen(main_filename, "r");
    if (fp != NULL) {
        return "ERROR\n";
    }
    fclose(fp);
    
    FILE* fs_file = fopen(main_filename, "a+");
    
    char content[1024];
    printf("Введите содержимое файла\n");
    scanf("%s", content);
    
    fprintf(fs_file, "%s\n", filename);
    fprintf(fs_file, "%s\n", content);
    fprintf(fs_file, "/\n");
    
    return "GOOD";
}

void modify_file(const char* fs_filename) {
    // Открываем файловую систему для чтения, чтобы проверить существует ли такой файл
    FILE* fs_file = fopen(fs_filename, "r");
    if (fs_file == NULL) {
        printf("ERROR: Не удалось открыть файловую систему\n");
        return;
    }
    fclose(fs_file);

    // Временный файл
    FILE* file = fopen(fs_filename, "w");
    if (file == NULL) {
        printf("ERROR: Не удалось создать временный файл\n");
        fclose(file);
        return;
    }

    // получаем новое содержимое
    char new_content[1024];
    printf("Введите новое содержимое для файла '%s':\n", filename);
    scanf(" %1023[^\n]", new_content);

    char line[256];
    int found = 0;
    int copying = 1;

    // Обрабатко файловой системы
    for (int i = 0; i <= MAX_SIZE; i++) {
        if (text[i] == '\0') {
            fprintf("\0", file); // закрываем слово
        } else {
            fprintf("%c", new_content[i], file);
        }
    }

    // Закрываем файл
    fclose(file);
}
