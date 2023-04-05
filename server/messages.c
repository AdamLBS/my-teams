/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "server.h"

void send_message_to_clients(char *s_uuid, char *msg, char *r_uuid)
{
    struct client *tmp;
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

void send_command(char *buffer)
{
    buffer += 6; char *r_uuid; char *s_uuid; char msg[MAX_BODY_LENGTH];
    memset(msg, 0, MAX_BODY_LENGTH); uuid_t uuid; int runs = 0; char *token;
    token = strtok(buffer, " ");
    if (token != NULL) {
        r_uuid = token;
        token = strtok(NULL, " ");
        strcpy(msg, token);
        token = strtok(NULL, " ");
        while (uuid_parse(token, uuid) == -1) {
            strcat(msg, " ");
            strcat(msg, token);
            token = strtok(NULL, " ");
            runs++;
        }
        s_uuid = token;
    }
    server_event_private_message_sended(s_uuid, r_uuid, msg);
    send_message_to_clients(s_uuid, msg, r_uuid);
}
