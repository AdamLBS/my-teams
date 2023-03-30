/*
** EPITECH PROJECT, 2023
** client_commands.c
** File description:
** client_commands
*/

#include "client.h"

void send_commands(void *handle, client_t *client)
{
    char *buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
    read(0, buffer, MAX_BODY_LENGTH);
    int val = 0;
    buffer[strlen(buffer) - 1] = '\0';
    if (strstr(buffer, "/login"))
        login_command(handle, client, buffer);
    if (strcmp(buffer, "/logout") == 0) {
        logout_command(handle, client, buffer); val = 1;
    }
    if (strstr(buffer, "/help"))
        help_command();
    if (strcmp(buffer, "/users") == 0)
        users_command(handle, client);
    else if (strstr(buffer, "/user"))
        user_command(handle, client, buffer);
    free(buffer);
    if (val == 1) {
        free(client->username);
        close(client->sock); exit(0);
    }
}
