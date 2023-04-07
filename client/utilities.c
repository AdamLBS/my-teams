/*
** EPITECH PROJECT, 2023
** utilities.c
** File description:
** utilities
*/

#include "client.h"

char *clean_text(char *text)
{
    char *new_text = malloc(sizeof(char) * strlen(text));
    int i = 0;
    int j = 0;
    while (text[i] != '\0') {
        if (text[i] != '"') {
            new_text[j] = text[i];
            j++;
        }
        i++;
    }
    new_text[j + 1] = '\0';
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
    while (getline(&line, &len, fd) != -1) {
        if (i == id) {
            fclose(fd);
            line[strlen(line) - 1] = '\0';
            return line;
        }
        i++;
    }
    return NULL;
}

int check_if_file_exist(char *team_uuid, char *dir)
{
    DIR *d = opendir(dir);
    struct dirent *direc;
    if (!d)
        return 0;
    while ((direc = readdir(d)) != NULL) {
        if (strstr(direc->d_name, team_uuid)) {
            closedir(d);
            return 1;
        }
    }
    closedir(d);
    return 0;
}
