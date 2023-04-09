/*
** EPITECH PROJECT, 2023
** utilities.c
** File description:
** utilities
*/

#include "client.h"

char *clean_text(char *text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '"')
            count++;
    }
    if (count == 0)
        return text;
    char *new_text = malloc(sizeof(char) * (strlen(text) - count + 1));
    memset(new_text, 0, strlen(text) - count + 1);
    int i = 0;
    int j = 0;
    while (text[i] != '\0') {
        if (text[i] != '"') {
            new_text[j] = text[i];
            j++;
        }
        i++;
    }
    return new_text;
}

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
    if (!fd)
        return NULL;
    while (getline(&line, &len, fd) != -1) {
        if (i == id) {
            fclose(fd); free(path); free(file);
            line[strlen(line) - 1] = '\0';
            return line;
        }
        i++;
    }
    fclose(fd); free(path); free(file);
    return NULL;
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
        char *file_title = get_file_line(line, uuid, dir);
        if (file_title && strcmp(file_title, title) == 0) {
            closedir(d); free(file_title); free(uuid);
            return 1;
        }
        if (file_title) free(file_title);
        free(uuid);
    }
    closedir(d); return 0;
}
