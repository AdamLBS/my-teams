/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "client.h"

void login_command(void *handle, client_t *client, char *buffer)
{
    char *username = strchr(buffer, ' ');
    if (username != NULL)
        username++;
    else {
        return;
    }
    client->username = strdup(username);
    ((int (*)(char const *, const char *))
    dlsym(handle, "client_event_logged_in"))(client->id, username);
}

void logout_command(void *handle, client_t *client)
{
    ((int (*)(char const *, const char *))
    dlsym(handle, "client_event_logged_out"))(client->id, client->username);
}
