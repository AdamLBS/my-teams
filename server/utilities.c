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
    fd_set read_fds;FD_ZERO(&read_fds);FD_SET(fileno(fd), &read_fds);
    select(fileno(fd) + 1, &read_fds, NULL, NULL, NULL);
    while (getline(&line, &len, fd) != -1) {
        if (i == id) {
            fclose(fd);
            return line;
        }
        fd_set read_fds;FD_ZERO(&read_fds);FD_SET(fileno(fd), &read_fds);
        select(fileno(fd) + 1, &read_fds, NULL, NULL, NULL);
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
    strcpy(path, dir); strcat(path, uuid); strcat(path, ".txt");
    char *to_put = malloc(sizeof(char) * (strlen(target) + 2));
    strcpy(to_put, target); to_put[strlen(target)] = '\n';
    to_put[strlen(target) + 1] = '\0';
    fd = fopen(path, "r");
    while (getline(&line, &len, fd) != -1) {
        file[i] = line;
        line = NULL;
        i++;
    }
    file[id] = strdup(to_put); fclose(fd); fd = fopen(path, "w");
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

char **get_file_data(char *path, int newline)
{
    FILE *fd = fopen(path, "r"); char buffer[256] = {0};
    fd_set read_fds;FD_ZERO(&read_fds);FD_SET(fileno(fd), &read_fds);
    select(fileno(fd) + 1, &read_fds, NULL, NULL, NULL);
    char *line = malloc(sizeof(char) * 512);
    memset(line, '\0', 512);int len = 0, i = 0;
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    while (read(fileno(fd), buffer, 1) > 0) {
        select(fileno(fd) + 1, &read_fds, NULL, NULL, NULL);
        if (buffer[0] == '\n') {
            newline == 1 ? strcat(line, "\n") : 0;
            file[i] = malloc(sizeof(char) * (len + 1));
            memset(file[i], '\0', len + 1); strcpy(file[i], line);
            free(line); line = NULL; len = 0; i++;
            line = malloc(sizeof(char) * 512); memset(line, '\0', 512);
        } else {
            strcat(line, buffer); len++;
        }
    }
    fclose(fd); return file;
}
