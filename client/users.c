/*
** EPITECH PROJECT, 2023
** users.c
** File description:
** users
*/

#include "client.h"

void users_command(client_t *client)
{
    send(client->sock, "/users\n", strlen("/users\n"), 0);
}

void receive_users(char *buffer, void *handle)
{
    for (int i = 0; i != 7; i++, buffer++);
    char *token = strtok(buffer, " ");
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

void receive_user(void *handle, char *buffer)
{
    int error = strstr(buffer, "ERROR") != NULL;
    for (int i = 0; i != 6; i++, buffer++);
    char *id = strtok(buffer, " ");
    if (error) {
        ((int (*)(char const *))
        dlsym(handle, "client_error_unknown_user"))(id);
        return;
    }
    char *username = strtok(NULL, " ");
    int is_connected = atoi(strtok(NULL, " "));
    ((int (*)(char const *, char const *, int))
    dlsym(handle, "client_print_user"))(id, username, is_connected);
}

void user_command(client_t *client, char *buffer)
{
    char *id_find = strchr(buffer, ' ');
    if (id_find != NULL)
        id_find++;
    else {
        id_find[0] = '\0';
    }
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", strlen("\n"), 0);
}
