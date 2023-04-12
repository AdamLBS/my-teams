/*
** EPITECH PROJECT, 2023
** client_commands.c
** File description:
** client_commands
*/

#include "client.h"

void subscribe_command(client_t *client, char *buffer)
{
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", 1, 0);
    char *team_uuid;
    buffer += 11;
    char *token = strtok(buffer, "\"");
    team_uuid = clean_text(token);
    client->team_uuid = strdup(team_uuid);
}

void other_commands(client_t *client, char *buffer)
{
    if (strcmp(buffer, "/users") == 0)
        users_command(client);
    if (strstr(buffer, "/user "))
        user_command(client, buffer);
    else if (strstr(buffer, "/use"))
        use_command(client, buffer);
    if (strcmp(buffer, "/info") == 0)
        info_command(client);
    if (strcmp(buffer, "/list") == 0)
        list_command(client);
    if (strstr(buffer, "/subscribed")) {
        subscribed_command(client, buffer); return;
    } if (strstr(buffer, "/subscribe"))
        subscribe_command(client, buffer);
}

void check_commands(char *buffer, client_t *client)
{
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
}

void send_commands(client_t *client)
{
    char buffer[MAX_BODY_LENGTH] = {0};
    if (read(0, buffer, MAX_BODY_LENGTH) > 0)
        strcat(client->in_buffer, buffer);
    if (!is_in_buffer_ended(client))
        return;
    if (strlen(client->in_buffer) > 0 )
        client->in_buffer[strlen(client->in_buffer) - 1] = '\0';
    if (strstr(client->in_buffer, "/login"))
        login_command(client, client->in_buffer);
    else if (strlen(client->in_buffer) > 0 && client->login == 0) {
        log_unauthorized(); memset(client->in_buffer, 0, 512); return;
    }
    check_commands(client->in_buffer, client);
    memset(client->in_buffer, 0, MAX_BODY_LENGTH);
}

void log_unauthorized(void)
{
    client_error_unauthorized();
    return;
}
