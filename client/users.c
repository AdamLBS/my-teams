/*
** EPITECH PROJECT, 2023
** users.c
** File description:
** users
*/

#include "client.h"

void users_command(void *handle, client_t *client)
{
    send(client->sock, "/users\n", strlen("/users\n"), 0);
    char line[MAX_BODY_LENGTH];
    if (recv(client->sock, line, MAX_BODY_LENGTH, 0) < 0) {
        printf("Error: recv\n");
        return;
    }
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
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", strlen("\n"), 0);
    char line[MAX_BODY_LENGTH];
    recv(client->sock, line, MAX_BODY_LENGTH, 0);
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
