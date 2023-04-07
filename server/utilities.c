/*
** EPITECH PROJECT, 2023
** utilities.c
** File description:
** utilities
*/

#include "server.h"

char *get_file_line(int id, char *uuid, char *dir)
{
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, dir);
    strcat(path, uuid);
    strcat(path, ".txt");
    fd = fopen(path, "r");
    while (getline(&line, &len, fd) != -1) {
        if (i == id) {
            fclose(fd);
            return line;
        }
        i++;
    }
    return NULL;
}

void set_file_line(int id, char *uuid, char *target, char *dir)
{
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, dir);
    strcat(path, uuid);
    strcat(path, ".txt");
    fd = fopen(path, "r");
    while (getline(&line, &len, fd) != -1) {
        file[i] = line;
        line = NULL;
        i++;
    }
    file[id] = strdup(target); fclose(fd); fd = fopen(path, "w");
    for (i = 0; file[i]; i++) fputs(file[i], fd);
    fclose(fd);
}

char *itoa(int num)
{
    int len = snprintf(NULL, 0, "%d", num);
    char* str = malloc(sizeof(char) * (len + 1));
    snprintf(str, len + 1, "%d", num);
    return str;
}

int check_if_file_exist(char *uuid, char *dir)
{
    DIR *d = opendir(dir);
    struct dirent *direc;
    if (!d)
        return 0;
    while ((direc = readdir(d)) != NULL) {
        if (strstr(direc->d_name, uuid)) {
            closedir(d);
            return 1;
        }
    }
    closedir(d);
    return 0;
}