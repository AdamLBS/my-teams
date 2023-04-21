/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** login_events
*/

#include "server.h"

void send_login_event(struct client *cli)
{
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (tmp->sock == cli->sock)
            continue;
        if (tmp->username == NULL)
            continue;
        send_data_to_socket(tmp->sock, "user_logged_in: ");
        send_data_to_socket(tmp->sock, cli->id);
        send_data_to_socket(tmp->sock, " ");
        send_data_to_socket(tmp->sock, cli->username);
        send_data_to_socket(tmp->sock, "\n");
    }
}

void send_logout_event(struct client *cli)
{
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (tmp->sock == cli->sock)
            continue;
        if (tmp->username == NULL)
            continue;
        if (tmp->sock == -1)
            continue;
        send_data_to_socket(tmp->sock, "user_logged_out: ");
        send_data_to_socket(tmp->sock, cli->id);
        send_data_to_socket(tmp->sock, " ");
        send_data_to_socket(tmp->sock, cli->username);
        send_data_to_socket(tmp->sock, "\n");
    }
}
