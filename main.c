#include <stdio.h>
#include "filesystem.h"

// Компиляция: gcc main.c filesystem.c -o fs_program
int main()
{
    while (1) {
        
        int file_action;
        printf("Ваше действие с файлом\n1 - Отркыть/Создать файл\n2 - Прочитать файл\n3 - Удаление файла\n4 -Добавить новый файла \n5 - Обновить файл\n0 -Выйти из программы\n");
        scanf("%d", &file_action);
    
        if (file_action == 0) break;
        
        char filename[255];
        printf("Input your file\n");
        scanf("%s", filename);
    
        FILE* fp;
        
    
        switch(file_action) {
            case 1:
                fp = create_open_file(filename);
                break;
            case 2:
                fp = fopen(filename, "r");
                printf("Результат:\n%s\n", view_file(filename));
                break;
            case 3:
                printf("Результат: %s\n", delete_file(filename));
                break;
            case 4:
                printf("Результат: %s\n", add_file(filename));
                break;
            case 5:
                printf("Результат: %s\n", modify_file(filename)); 
                break;
            default:
                printf("Ошибка такого действие еще нет");
        }
    }

    return 1;
}
