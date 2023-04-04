/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** handle_commands
*/

#include "client.h"

void handle_received_data(void *handle, client_t *client)
{
    if (strstr(client->buffer, "receive:"))
    receive_message(handle, client->buffer);
    if (strstr(client->buffer, "users:"))
        receive_users(client->buffer, handle);
    if (strstr(client->buffer, "user:"))
        receive_user(handle, client->buffer);
    if (strstr(client->buffer, "LOGIN OK\n")) {
        ((int (*)(char const *, const char *))
        dlsym(handle, "client_event_logged_in"))
        (client->id, client->username);
    }
    if (strstr(client->buffer, "LOGOUT OK\n")) {
        ((int (*)(char const *, const char *))
        dlsym(handle, "client_event_logged_out"))
        (client->id, client->username);
        free(client->username); close(client->sock); exit(0);
    }
}
