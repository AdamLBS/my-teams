/*
** EPITECH PROJECT, 2023
** create_reply.c
** File description:
** create_reply
*/

#include "client.h"

void send_reply(client_t *client, char *time, char *r_body)
{
    send(client->sock, time, (strlen(time)), 0);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, r_body, strlen(r_body), 0);
    send(client->sock, "\"\n", 2, 0);
}

void create_reply_command(client_t *client, char *buffer)
{
    time_t curTime = time( NULL ); char *time = ctime(&curTime);
    time[strlen(time) - 1] = '\0';
    char r_uuid[37]; uuid_t uuid; uuid_generate_random(uuid);
    uuid_unparse(uuid, r_uuid); buffer += 8; buffer[strlen(buffer)] = '\0';
    char *r_body; char *token = strtok(buffer, "\"");
    r_body = token; r_body = clean_text(r_body);
    client->s_reply->r_body = strdup(r_body);
    client->s_reply->t_time = curTime;
    send(client->sock, "create_reply", 12, 0); send(client->sock, " ", 1, 0);
    send(client->sock, r_uuid, 36, 0);send(client->sock, " ", 1, 0);
    send(client->sock, client->team_uuid, 36, 0);send(client->sock, " ", 1, 0);
    send(client->sock, client->channel_uuid, 36, 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, client->thread_uuid, 36, 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, client->id, 36, 0); send(client->sock, " \"", 2, 0);
    send_reply(client, time, r_body);
}
