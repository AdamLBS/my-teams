/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL : Ubuntu]
** File description:
** load_users
*/

#include "server.h"
#include <stdio.h>

void free_userlist(char ***userList)
{
    for (int i = 0; userList[i]; i++) {
        for (int j = 0; userList[i][j]; j++) {
            free(userList[i][j]);
        }
        free(userList[i]);
    }
    free(userList);
}

void load_users_from_save(void)
{
    DIR *d; struct dirent *dir; char *path = NULL;
    char ***userList = malloc(sizeof(char **) * 100);
    memset(userList, 0, 100);
    int index = 0; d = opendir("users/");
    if (!d)
        return;
    while ((dir = readdir(d)) != NULL) {
        path = dir->d_name;
        if (strlen(path) > 4 && !strcmp(path + strlen(path) - 4, ".txt")) {
            int size = strlen("users/") + strlen(dir->d_name) + 1;
            char *fullpath = malloc(sizeof(char ) * size);
            memset(fullpath, '\0', size);
            strcpy(fullpath, "users/");
            strcat(fullpath, dir->d_name);
            char **val = read_user_from_save(fullpath);
            free(fullpath); userList[index] = val;
            index++;
        }
    }
    send_user_loaded(userList); closedir(d); free_userlist(userList);
}

void send_user_loaded(char ***userList)
{
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(STDERR_FILENO, &read_fds);
    for (int i = 0; userList[i] ; i++) {
        select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
        server_event_user_loaded(userList[i][1], userList[i][0]);
    }
}

char **read_user_from_save(char *path)
{
    FILE *fptr = fopen(path, "r");
    if (!fptr) return NULL;
    fd_set read_fds;FD_ZERO(&read_fds);FD_SET(fileno(fptr), &read_fds);
    select(fileno(fptr) + 1, &read_fds, NULL, NULL, NULL);
    size_t len = 0; char *line = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(line, '\0', MAX_BODY_LENGTH);
    char **array = malloc(sizeof(char * ) * 100);
    memset(array, 0, 100);char buffer[256] = {0};
    int i = 0;
    while (read(fileno(fptr), buffer, 1) > 0) {
        select(fileno(fptr) + 1, &read_fds, NULL, NULL, NULL);
        if (buffer[0] == '\n') {
            array[i] = malloc(sizeof(char) * (len + 1));
            memset(array[i], '\0', len + 1); strcpy(array[i], line);
            free(line); line = NULL; len = 0; i++;
            line = malloc(sizeof(char) * 512); memset(line, '\0', 512);
        } else {
            strcat(line, buffer); len++;
        }
    } fclose(fptr); return array;
}
