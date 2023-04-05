/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "server.h"

void send_command(char *buffer)
{
    buffer += 6; char *r_uuid; char *s_uuid; char msg[MAX_BODY_LENGTH]; char *token;
    memset(msg, 0, MAX_BODY_LENGTH);
    uuid_t uuid;
    token = strtok(buffer, " "); struct client *tmp;
    int runs = 0;
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
    free(token);
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
