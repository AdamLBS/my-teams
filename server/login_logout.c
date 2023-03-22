/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "server.h"

void login_command(void *handle, struct client *client, char *buffer)
{
    char *username = strchr(buffer, ' ');
    if (username != NULL)
        username++;
    else {
        return;
    }
    client->username = username;
    ((int (*)(char const *))
    dlsym(handle, "server_event_user_logged_in"))(client->id);
}

void logout_command(void *handle, struct client *client)
{
    ((int (*)(char const *))
    dlsym(handle, "server_event_user_logged_out"))(client->id);
}
