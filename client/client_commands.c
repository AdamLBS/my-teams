/*
** EPITECH PROJECT, 2023
** client_commands.c
** File description:
** client_commands
*/

#include "client.h"

void other_commands(client_t *client, char *buffer)
{
    if (strcmp(buffer, "/users") == 0)
        users_command(client);
    else if (strstr(buffer, "/user"))
        user_command(client, buffer);
    if (strstr(buffer, "/use"))
        use_command(client, buffer);
    if (strcmp(buffer, "/info") == 0)
        info_command(client);
}

void send_commands(client_t *client)
{
    char *buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(buffer, 0, MAX_BODY_LENGTH); read(0, buffer, MAX_BODY_LENGTH);
    buffer[strlen(buffer) - 1] = '\0';
    if (strstr(buffer, "/login"))
        login_command(client, buffer);
    if (strlen(buffer) > 0 && client->username[0] == '\0') {
        log_unauthorized(); free(buffer); return;
    }
    if (strcmp(buffer, "/logout") == 0)
        logout_command(client, buffer);
    if (strstr(buffer, "/help"))
        help_command();
    if (strstr(buffer, "/send"))
        send_command(buffer, client);
    if (strstr(buffer, "/create"))
        check_create_commands(client, buffer);
    if (strstr(buffer, "/messages"))
        send_messages_command(buffer, client);
    other_commands(client, buffer);
    free(buffer);
}

void log_unauthorized(void)
{
    client_error_unauthorized();
    return;
}
