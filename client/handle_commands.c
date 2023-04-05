/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** handle_commands
*/

#include "client.h"

void handle_received_data(client_t *client)
{
    if (strstr(client->buffer, "receive:"))
        receive_message(client->buffer);
    if (strstr(client->buffer, "users:"))
        receive_users(client->buffer);
    if (strstr(client->buffer, "user:"))
        receive_user(client->buffer);
    if (strstr(client->buffer, "LOGIN OK\n")) {
        client_event_logged_in(client->id, client->username);
    }
    if (strstr(client->buffer, "LOGOUT OK\n")) {
        client_event_logged_out(client->id, client->username);
        free(client->username); close(client->sock); exit(0);
    }
}
