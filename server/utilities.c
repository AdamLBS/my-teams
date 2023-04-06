/*
** EPITECH PROJECT, 2023
** utilities.c
** File description:
** utilities
*/

#include "server.h"

char *get_user_line(int id, char *uuid)
{
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, "users/");
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

void set_user_line(int id, char *uuid, char *target)
{
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, "users/");
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