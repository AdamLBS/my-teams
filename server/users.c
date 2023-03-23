/*
** EPITECH PROJECT, 2023
** users.c
** File description:
** users
*/

#include "server.h"

void users_command(struct client *client)
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

void user_command(struct client *client, char *buffer)
{
    char *id = strchr(buffer, ' ');
    if (id != NULL)
        id++;
    else {
        dprintf(client->sock, "ERROR\n");
        return;
    }
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (strcmp(tmp->id, id) == 0) {
            if (tmp->username != NULL) {
                dprintf(client->sock, "%s ", tmp->id);
                dprintf(client->sock, "%s ", tmp->username);
                dprintf(client->sock, (tmp->sock > 0 ? "1\n" : "0\n"));
                return;
            }
        }
    }
    dprintf(client->sock, "ERROR\n");
}