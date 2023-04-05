/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "server.h"

void send_command(char *buffer)
{
    buffer += 6; char *r_uuid; char *s_uuid; char *msg; char *token;
    token = strtok(buffer, " "); struct client *tmp;
    if (token != NULL) {
        r_uuid = token;
        token = strtok(NULL, " ");
        msg = token;
        token = strtok(NULL, " ");
        s_uuid = token;
    }
    server_event_private_message_sended(s_uuid, r_uuid, msg);
    LIST_FOREACH(tmp, &head, next) {
        if (strcmp(r_uuid, tmp->id) == 0) {
            char *nbuff = malloc(sizeof(char) * MAX_BODY_LENGTH);
            nbuff = strcpy(nbuff, "receive: ");
            nbuff = strcat(nbuff, s_uuid); nbuff = strcat(nbuff, " ");
            nbuff = strcat(nbuff, msg); nbuff = strcat(nbuff, "\n");
            send(tmp->sock, nbuff, strlen(nbuff), 0);
        }
    }
}
