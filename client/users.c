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
    usleep(2000);
    char line[MAX_BODY_LENGTH];
    read(client->sock, line, MAX_BODY_LENGTH);
    line[strlen(line) - 1] = '\0';
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
