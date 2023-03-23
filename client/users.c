/*
** EPITECH PROJECT, 2023
** users.c
** File description:
** users
*/

#include "client.h"

void users_command(void *handle, client_t *client)
{
    dprintf(client->sock, "/users\n");
    char line[MAX_BODY_LENGTH];
    read(client->sock, line, MAX_BODY_LENGTH);
    char *token = strtok(line, " ");
    while (token != NULL) {
        char *id = token;
        token = strtok(NULL, " ");
        char *username = token;
        token = strtok(NULL, " ");
        int is_connected = atoi(token);
        token = strtok(NULL, " ");
        ((int (*)(char const *, char const *, int))
        dlsym(handle, "client_print_users"))(id, username, is_connected);
    }
}

void user_command(void *handle, client_t *client, char *buffer)
{
    char *id_find = strchr(buffer, ' ');
    if (id_find != NULL)
        id_find++;
    else {
        id_find[0] = '\0';
    }
    dprintf(client->sock, "%s\n", buffer);
    char line[MAX_BODY_LENGTH];
    read(client->sock, line, MAX_BODY_LENGTH);
    if (strstr(line, "ERROR")) {
        ((int (*)(char const *))
        dlsym(handle, "client_error_unknown_user"))(id_find);
        return;
    }
    char *id = strtok(line, " ");
    char *username = strtok(NULL, " ");
    int is_connected = atoi(strtok(NULL, " "));
    ((int (*)(char const *, char const *, int))
    dlsym(handle, "client_print_user"))(id, username, is_connected);
}
