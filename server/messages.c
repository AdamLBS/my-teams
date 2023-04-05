/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "server.h"

void send_message_to_clients(char *s_uuid, char *msg, char *r_uuid)
{
    save_message_receiver(msg, s_uuid, r_uuid);
    save_message_sender(msg, s_uuid, r_uuid);
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

void send_command(char *buffer, struct client *client)
{
    buffer += 6; char *r_uuid; char *s_uuid; char msg[MAX_BODY_LENGTH];
    memset(msg, 0, MAX_BODY_LENGTH); uuid_t uuid; int runs = 0; char *token;
    token = strtok(buffer, " ");
    if (token != NULL) {
        r_uuid = token; token = strtok(NULL, " "); if (!token) return;
        strcpy(msg, token); if (!token) return;token = strtok(NULL, " ");
        while (token && uuid_parse(token, uuid) == -1) {
            strcat(msg, " ");  strcat(msg, token);
            token = strtok(NULL, " "); runs++;
        }
        s_uuid = token;
    }
    if (s_uuid == NULL) {
        send_error(client, r_uuid);
        return;
    }
    server_event_private_message_sended(s_uuid, r_uuid, msg);
    send_message_to_clients(s_uuid, msg, r_uuid);
}

void send_error(struct client *client, char *id)
{
    send(client->sock, "user: ", 6, 0);
    send(client->sock, id, strlen(id), 0);
    send(client->sock, " ERROR\n", 7, 0);
}
