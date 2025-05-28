#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1.1 открыть (или создать и открыть) файл файловой системы "logo.txt"
FILE* fs_open(const char* filename) {
    FILE* fp = fopen(filename, "r+"); // попытка открыть для чтения и записи
    if (!fp) {
        fp = fopen(filename, "w+");   // если нет, создать и открыть
    }
    return fp; // вернуть файл или NULL
}

// Вспомогательная функция: считывает весь файл в строку
char* read_all_content(FILE* fp) {
    if (!fp) return NULL;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size < 0) return NULL;
    fseek(fp, 0, SEEK_SET);
    char* buffer = malloc(size+1);
    if (!buffer) return NULL;
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';
    return buffer;
}

// 1.2 посмотреть 1 файл внутри файловой системы "logo.png"
char* fs_read_file(FILE* fs, const char* filename) {
    if (!fs || !filename) return NULL;

    char* content = read_all_content(fs);
    if (!content) return NULL;

    char* line;
    char* saveptr;
    char* result = NULL;
    int found = 0;

    line = strtok_r(content, "\n", &saveptr);
    while (line) {
        if (strcmp(line, filename) == 0) {
            found = 1;
            size_t bufsize = 1024;
            size_t len = 0;
            result = malloc(bufsize);
            if (!result) {
                free(content);
                return NULL;
            }
            result[0] = '\0';

            line = strtok_r(NULL, "\n", &saveptr);
            while (line && line[0] != '/') {
                size_t linelen = strlen(line);
                if (len + linelen + 2 > bufsize) {
                    bufsize *= 2;
                    char* tmp = realloc(result, bufsize);
                    if (!tmp) {
                        free(result);
                        free(content);
                        return NULL;
                    }
                    result = tmp;
                }
                strcat(result, line);
                strcat(result, "\n");
                len += linelen + 1;
                line = strtok_r(NULL, "\n", &saveptr);
            }
            break;
        }
        line = strtok_r(NULL, "\n", &saveptr);
    }

    free(content);
    return result; // NULL если не найдено
}

// 1.3 удалить файл внутри файловой системы "logo.png"
int fs_delete_file(const char* fsname, const char* filename) {
    if (!fsname || !filename) return -1;

    FILE* fs = fopen(fsname, "r+");
    if (!fs) return -1;

    char* content = read_all_content(fs);
    if (!content) {
        fclose(fs);
        return -1;
    }

    #define MAX_LINES 10000
    char* lines[MAX_LINES];
    int lines_count = 0;

    char* line;
    char* saveptr;
    line = strtok_r(content, "\n", &saveptr);
    while (line && lines_count < MAX_LINES) {
        lines[lines_count++] = line;
        line = strtok_r(NULL, "\n", &saveptr);
    }

    int start_idx = -1;
    for (int i = 0; i < lines_count; i++) {
        if (strcmp(lines[i], filename) == 0) {
            start_idx = i;
            break;
        }
    }
    if (start_idx == -1) { // файл не найден
        free(content);
        fclose(fs);
        return -1;
    }

    int end_idx = lines_count;
    for (int i = start_idx + 1; i < lines_count; i++) {
        if (lines[i][0] == '/') {
            end_idx = i;
            break;
        }
    }

    freopen(fsname, "w", fs); // очистить и открыть для записи

    for (int i = 0; i < lines_count; i++) {
        if (i < start_idx ||
