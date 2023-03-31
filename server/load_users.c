/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL : Ubuntu]
** File description:
** load_users
*/

#include "server.h"
#define _GNU_SOURCE
#include <stdio.h>

void load_users_from_save(void *handle)
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
            userList[index] = val;
            index++;
        }
    }
    send_user_loaded(userList, handle);
}

void send_user_loaded(char ***userList, void *handle)
{
    for (int i = 0; userList[i] ; i++) {
        ((int (*)(char const *, char const *))
        dlsym(handle, "server_event_user_loaded"))
        (userList[i][1], userList[i][0]);
    }
}

char **read_user_from_save(char *path)
{
    FILE *fptr = fopen(path, "r");
    if (!fptr)
        return NULL;
    size_t len = 0;
    char *line = NULL;
    char **array = malloc(sizeof(char * ) * 10);
    memset(array, 0, 10);
    int i = 0;
    while (getline(&line, &len, fptr) != -1) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        array[i] = line;
        line = NULL;
        i++;
    }
    return array;
}