/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "server.h"

void login_command(void *handle, struct client *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    if (str != NULL)
        str++;
    else {
        return;
    }
    client->username = strdup(strtok(str, " "));
    client->id = strdup(strtok(NULL, " "));
    if (do_user_exists(client->id) == 0) {
        save_user(client->id, client->username);
        ((int (*)(char const *, char const *))
        dlsym(handle, "server_event_user_created"))(client->id, client->username);    
    } else {
        ((int (*)(char const *, char const *))
        dlsym(handle, "server_event_user_loaded"))(client->id, client->username);
    }
    ((int (*)(char const *))
    dlsym(handle, "server_event_user_logged_in"))(client->id);
}

void logout_command(void *handle, struct client *client)
{
    ((int (*)(char const *))
    dlsym(handle, "server_event_user_logged_out"))(client->id);
}
