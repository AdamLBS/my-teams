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
        send(tmp->sock, "user_logged_in: ", 16, 0);
        send(tmp->sock, cli->id, strlen(cli->id), 0);
        send(tmp->sock, " ", 1, 0);
        send(tmp->sock, cli->username, strlen(cli->username), 0);
        send(tmp->sock, "\n", 1, 0);
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
        send(tmp->sock, "user_logged_out: ", 17, 0);
        send(tmp->sock, cli->id, strlen(cli->id), 0);
        send(tmp->sock, " ", 1, 0);
        send(tmp->sock, cli->username, strlen(cli->username), 0);
        send(tmp->sock, "\n", 1, 0);
    }
}
