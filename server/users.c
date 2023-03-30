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
    char *str = malloc(sizeof(char) * MAX_BODY_LENGTH);
    LIST_FOREACH(tmp, &head, next) {
        if (val)
            str = strcat(str, " ");
        if (tmp->username != NULL) {
            str = copy == 1 ? strcpy(str, tmp->id) : strcat(str, tmp->id);
            str = strcat(str, " ");
            str = strcat(str, tmp->username);
            str = strcat(str, " ");
            str = strcat(str, (tmp->sock > 0 ? "1" : "0"));
            val = 1, copy = 0;
        }
    }
    str = strcat(str, "\n");
    send(client->sock, str, strlen(str), 0);
    free(str);
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
