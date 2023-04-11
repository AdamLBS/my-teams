/*
** EPITECH PROJECT, 2023
** check_error.c
** File description:
** check_error
*/

#include "server.h"

int check_if_title_exist(char *title, char *dir)
{
    DIR *d = opendir(dir);
    struct dirent *direc;
    if (!d) return 0;
    int line = (strcmp(dir, "./teams/") == 0
    || strcmp(dir, "./channels/") == 0) ? 1 : 3;
    while ((direc = readdir(d)) != NULL) {
        if (direc->d_name[0] == '.' || strcmp(direc->d_name, "tuto.md") == 0)
            continue;
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, direc->d_name, 36);
        char *file_title = get_file_line_n(line, uuid, dir);
        if (file_title && strcmp(file_title, title) == 0) {
            closedir(d); free(file_title); free(uuid);
            return 1;
        }
        if (file_title) free(file_title);
        free(uuid);
    }
    closedir(d); return 0;
}