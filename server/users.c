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
    int copy = 1;
    char *buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
    LIST_FOREACH(tmp, &head, next) {
        if (val)
            buffer = strcat(buffer, " ");
        if (tmp->username != NULL) {
            buffer = copy == 1 ? strcpy(buffer, tmp->id) : strcat(buffer, tmp->id);
            buffer = strcat(buffer, " ");
            buffer = strcat(buffer, tmp->username);
            buffer = strcat(buffer, " ");
            buffer = strcat(buffer, (tmp->sock > 0 ? "1" : "0"));
            val = 1, copy = 0;
        }
    }
    buffer = strcat(buffer, "\n");
    send(client->sock, buffer, strlen(buffer), 0);
    free(buffer);
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
    char *buf = malloc(sizeof(char) * MAX_BODY_LENGTH);
    LIST_FOREACH(tmp, &head, next) {
        if (strcmp(tmp->id, id) == 0) {
            if (tmp->username != NULL) {
                buf = strcpy(buf, tmp->id); buf = strcat(buf, " ");
                buf = strcat(buf, tmp->username); buf = strcat(buf, " ");
                buf = strcat(buf, (tmp->sock > 0 ? "1\n" : "0\n"));
                send(client->sock, buf, strlen(buf), 0); free(buf); return;
            }
        }
    }
    dprintf(client->sock, "ERROR\n");
}
