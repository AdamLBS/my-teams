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
    struct client *tmp;
    bool hasReceived = false;
    LIST_FOREACH(tmp, &head, next) {
        if (strcmp(r_uuid, tmp->id) == 0) {
            hasReceived = true;
            char *nbuff = malloc(sizeof(char) * MAX_BODY_LENGTH);
            nbuff = strcpy(nbuff, "receive: ");
            nbuff = strcat(nbuff, s_uuid); nbuff = strcat(nbuff, " ");
            nbuff = strcat(nbuff, msg); nbuff = strcat(nbuff, "\n");
            send(tmp->sock, nbuff, strlen(nbuff), 0);
            free(nbuff);
        }
    }
    save_message_sender(msg, s_uuid, r_uuid, hasReceived);
}

void send_command(char *buffer, struct client *client)
{
    buffer += 6; char *r_uuid; char *s_uuid; uuid_t uuid; char *msg;
    int runs = 0; char *token; token = strtok(buffer, " ");
    msg = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(msg, 0, MAX_BODY_LENGTH);
    if (token != NULL) {
        r_uuid = token; token = strtok(NULL, " "); if (!token) return;
        strcpy(msg, token); if (!token) return;token = strtok(NULL, " ");
        while (token && uuid_parse(token, uuid) == -1) {
            strcat(msg, " ");  strcat(msg, token);
            token = strtok(NULL, " "); runs++;
        }
        s_uuid = token;
    }
    r_uuid = remove_quotes_send_cmd(r_uuid); msg = remove_quotes_send_cmd(msg);
    if (!r_uuid || !msg) return;
    if (s_uuid == NULL || check_if_file_exist(r_uuid, "./users") == 0) {
        send_error(client, r_uuid); return;
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

char *remove_quotes_send_cmd(char *str)
{
    if (str[0] == '"' && str[strlen(str) - 1] == '"') {
        str[strlen(str) - 1] = '\0';
        str++;
    } else {
        return NULL;
    }
    return str;
}
