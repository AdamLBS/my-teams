/*
** EPITECH PROJECT, 2023
** users.c
** File description:
** users
*/

#include "server.h"

void users_command(void *handle, struct client *client)
{
    struct client *tmp;
    int val = 0;
    LIST_FOREACH(tmp, &head, next) {
        if (val)
            dprintf(client->sock, " ");
        if (tmp->username != NULL) {
            dprintf(client->sock, "%s ", tmp->id);
            dprintf(client->sock, "%s ", tmp->username);
            dprintf(client->sock, (tmp->sock > 0 ? "1" : "0"));
            val = 1;
        }
    }
    dprintf(client->sock, "\n");
}
