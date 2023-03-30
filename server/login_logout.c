/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "server.h"

void login_command(void *handle, struct client *client, char *buffer)
{
    printf("login_command\n");
    char *str = strchr(buffer, ' ');
    if (str != NULL)
        str++;
    else {
        return;
    }
    client->username = strdup(strtok(str, " "));
    client->id = strdup(strtok(NULL, " "));
    // recv(client->sock, client->id, sizeof(client->id), 0);
    ((int (*)(char const *))
    dlsym(handle, "server_event_user_logged_in"))(client->id);
}

void logout_command(void *handle, struct client *client)
{
    ((int (*)(char const *))
    dlsym(handle, "server_event_user_logged_out"))(client->id);
}
