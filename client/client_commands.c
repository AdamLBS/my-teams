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
    if (client->s_team->t_uuid != NULL)
        free(client->s_team->t_uuid);
    client->s_team->t_uuid = strdup(team_uuid);
}

void unsubscribe_command(client_t *client, char *buffer)
{
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", 1, 0);
    char *team_uuid;
    buffer += 13;
    char *token = strtok(buffer, "\"");
    team_uuid = clean_text(token);
    if (client->s_team->t_uuid != NULL)
        free(client->s_team->t_uuid);
    client->s_team->t_uuid = strdup(team_uuid);
}

void other_commands(client_t *client, char *buffer)
{
    if (strcmp(buffer, "/users") == 0)
        users_command(client);
    if (strncmp(buffer, "/user ", 6) == 0)
        user_command(client, buffer);
    else if (strncmp(buffer, "/use", 4) == 0)
        use_command(client, buffer);
    if (strcmp(buffer, "/info") == 0)
        info_command(client);
    if (strcmp(buffer, "/list") == 0)
        list_command(client);
    if (strncmp(buffer, "/subscribed", 11) == 0) {
        subscribed_command(client, buffer); return;
    } if (strncmp(buffer, "/subscribe", 10) == 0)
        subscribe_command(client, buffer);
    if (strncmp(buffer, "/unsubscribe", 12) == 0)
        unsubscribe_command(client, buffer);
}

void check_commands(char *buffer, client_t *client)
{
    if (strcmp(buffer, "/logout") == 0)
        logout_command(client, buffer);
    if (strncmp(buffer, "/help", 5) == 0)
        help_command();
    if (strncmp(buffer, "/send", 5) == 0)
        send_command(buffer, client);
    if (strncmp(buffer, "/create", 7) == 0)
        check_create_commands(client, buffer);
    if (strncmp(buffer, "/messages", 9) == 0)
        send_messages_command(buffer, client);
    other_commands(client, buffer);
}

void send_commands(client_t *client)
{
    char buffer[MAX_BODY_LENGTH] = {0};
    if (read(0, buffer, 1) > 0)
        strcat(client->in_buffer, buffer);
    if (!is_in_buffer_ended(client))
        return;
    if (strlen(client->in_buffer) > 0 )
        client->in_buffer[strlen(client->in_buffer) - 1] = '\0';
    if (strncmp(client->in_buffer, "/login", 6) == 0)
        login_command(client, client->in_buffer);
    else if (strlen(client->in_buffer) > 0 && client->login == 0) {
        client_error_unauthorized(); memset(client->in_buffer, 0, 512); return;
    }
    check_commands(client->in_buffer, client);
    memset(client->in_buffer, 0, MAX_BODY_LENGTH);
}
