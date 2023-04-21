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
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(STDERR_FILENO, &read_fds);
    select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
    client_event_logged_in(id, username);
}

void get_client_logout_event(client_t *client)
{
    client->buffer[strlen(client->buffer) - 1] = '\0';
    strtok(client->buffer, " ");
    char *id, *username;
    id = strtok(NULL, " ");
    username = strtok(NULL, " ");
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(STDERR_FILENO, &read_fds);
    select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
    client_event_logged_out(id, username);
}
