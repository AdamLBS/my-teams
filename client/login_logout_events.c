/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** login_logout_events
*/

#include "client.h"

void get_client_login_event(client_t *client)
{
    client->buffer[strlen(client->buffer) - 1] = '\0';
    strtok(client->buffer, " ");
    char *id, *username;
    id = strtok(NULL, " ");
    username = strtok(NULL, " ");
    client_event_logged_in(id, username);
}

void get_client_logout_event(client_t *client)
{
    client->buffer[strlen(client->buffer) - 1] = '\0';
    strtok(client->buffer, " ");
    char *id, *username;
    id = strtok(NULL, " ");
    username = strtok(NULL, " ");
    client_event_logged_out(id, username);
}
