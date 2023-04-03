/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** handle_commands
*/

#include "client.h"

void handle_received_data(char *buffer, void *handle, client_t *client)
{
    if (strstr(buffer, "receive:"))
    receive_message(handle, buffer);
    if (strstr(buffer, "LOGIN OK\n")) {
        ((int (*)(char const *, const char *))
        dlsym(handle, "client_event_logged_in"))
        (client->id, client->username);
    }
    if (strstr(buffer, "LOGOUT OK\n")) {
        ((int (*)(char const *, const char *))
        dlsym(handle, "client_event_logged_out"))
        (client->id, client->username);
        free(client->username); close(client->sock); exit(0);
    }
}
