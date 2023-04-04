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
    memset(buffer, 0, MAX_BODY_LENGTH); read(0, buffer, MAX_BODY_LENGTH);
    buffer[strlen(buffer) - 1] = '\0';
    if (strstr(buffer, "/login"))
        login_command(client, buffer);
    if (strlen(buffer) > 0 && client->username[0] == '\0') {
        log_unauthorized(handle); return;
    }
    if (strcmp(buffer, "/logout") == 0)
        logout_command(client, buffer);
    if (strstr(buffer, "/help"))
        help_command();
    if (strstr(buffer, "/send"))
        send_command(buffer, client);
    if (strcmp(buffer, "/users") == 0)
        users_command(client);
    else if (strstr(buffer, "/user"))
        user_command(client, buffer);
    free(buffer);
}

void log_unauthorized(void *handle)
{
    ((int (*)(void))
    dlsym(handle, "client_error_unauthorized"))();
    return;
}
