/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "server.h"

void login_command(struct client *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    if (str != NULL)
        str++;
    else
        return;
    client->username = strdup(strtok(str, "\""));
    client->id = strdup(strtok(NULL, " "));
    if (do_user_exists(client->id) == 0) {
        save_user(client->id, client->username);
        server_event_user_created(client->id, client->username);
    }
    server_event_user_logged_in(client->id);
    set_user_to_logged_in(client->id);
    send(client->sock, "LOGIN OK\n", 9, 0);
    check_pending_messages(client);
}

void logout_command(struct client *client)
{
    server_event_user_logged_out(client->id);
    send(client->sock, "LOGOUT OK\n", 10, 0);
    set_user_to_logged_out(client->id);
}

void catch_client_logout(struct client *client)
{
    if (client->username) {
        server_event_user_logged_out(client->id);
        set_user_to_logged_out(client->id);
    }
    client->sock = -1;
}
