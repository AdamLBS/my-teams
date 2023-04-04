/*
** EPITECH PROJECT, 2023
** users.c
** File description:
** users
*/

#include "server.h"

void users_command(struct client *client)
{
    get_users_from_save(client);
}

void user_command(struct client *client, char *buffer)
{
    char *id = strchr(buffer, ' ');
    if (id != NULL)
        id++;
    else {
        dprintf(client->sock, "ERROR\n");
        return;
    }
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, "users/"); strcat(path, id); strcat(path, ".txt");
    FILE *fd = fopen(path, "r");
    if (fd == 0) {
        send(client->sock, "user: ", 6, 0);
        send(client->sock, id, strlen(id), 0);
        send(client->sock, " ERROR\n", 7, 0);
        free(path);
        return;
    }
    char **val = read_user_from_save(path);
    send_user(val, client);
}

void get_users_from_save(struct client *client)
{
    DIR *d; struct dirent *dir; char *path = NULL;
    char ***userList = malloc(sizeof(char **) * 100);
    memset(userList, 0, 100);
    int index = 0; d = opendir("users/");
    if (!d) return;
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
    send_users(userList, client);
}

void send_users(char ***userList, struct client *client)
{
    send(client->sock, "users: ", 7, 0);
    for (int i = 0; userList[i]; i++) {
        if (i != 0)
            send(client->sock, " ", 1, 0);
        send(client->sock, userList[i][0], strlen(userList[i][0]), 0);
        send(client->sock, " ", 1, 0);
        send(client->sock, userList[i][1], strlen(userList[i][1]), 0);
        send(client->sock, " ", 1, 0);
        send(client->sock, userList[i][2], strlen(userList[i][2]), 0);
    }
    send(client->sock, "\n", 1, 0);
}

void send_user(char **user, struct client *client)
{
    send(client->sock, "user: ", 6, 0);
    send(client->sock, user[0], strlen(user[0]), 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, user[1], strlen(user[1]), 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, user[2], strlen(user[2]), 0);
    send(client->sock, "\n", 1, 0);
}
