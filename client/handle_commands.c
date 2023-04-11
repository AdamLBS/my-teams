/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** handle_commands
*/

#include "client.h"

void free_client(client_t *client)
{
    free(client->username);
    close(client->sock);
    free(client->in_buffer);
    if (client->context >= 1 && client->team_uuid != NULL)
        free(client->team_uuid);
    if (client->context >= 2 && client->channel_uuid != NULL)
        free(client->channel_uuid);
    if (client->context >= 3 && client->thread_uuid != NULL)
        free(client->thread_uuid);
    exit(0);
}

void handle_received_data(client_t *client)
{
    if (strstr(client->buffer, "receive:"))
        receive_message(client->buffer);
    if (strstr(client->buffer, "users:"))
        receive_users(client->buffer);
    if (strstr(client->buffer, "user:"))
        receive_user(client->buffer);
    if (strstr(client->buffer, "msg_history:"))
        receive_messages_history(client->buffer, client);
    if (strstr(client->buffer, "LOGIN OK\n")) {
        client_event_logged_in(client->id, client->username);client->login = 1;
    }
    if (strstr(client->buffer, "LOGOUT OK\n")) {
        client_event_logged_out(client->id, client->username);
        free_client(client);
    }
    if (strstr(client->buffer, "/info"))
        info_command_receive(client, client->buffer);
    if (strstr(client->buffer, "/list"))
        list_command_receive(client, client->buffer);
}
