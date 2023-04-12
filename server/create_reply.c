/*
** EPITECH PROJECT, 2023
** create_reply.c
** File description:
** create_reply
*/

#include "server.h"

int check_reply_error(struct client *client, char *team_uuid, char *c_uuid
, char *t_uuid)
{
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
        send(client->sock, "311\n", 4, 0); return 1;
    }
    if (check_if_file_exist(c_uuid, "./channels/") == 0) {
        send(client->sock, "321\n", 4, 0); return 1;
    }
    if (check_if_file_exist(t_uuid, "./threads/") == 0) {
        send(client->sock, "331\n", 4, 0); return 1;
    }
    if (check_permissions(client, team_uuid) == 1) {
        send(client->sock, "101\n", 4, 0); return 1;
    }
    return 0;
}

void put_r(struct reply *reply, char *uuid, char *tm_uuid, char *t_uuid)
{
    reply->t_uuid = strdup(t_uuid);
    reply->tm_uuid = strdup(tm_uuid);
    reply->o_uuid = strdup(uuid);
    create_reply_file(reply);
}


void send_info_reply(struct client *client, int i, int j, int k, int n)
{
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (check_permissions(tmp, client->teams[i]->uuid) == 1) continue;
        send(tmp->sock, "941 \"", 5, 0);
        send(tmp->sock, client->teams[i]->channels[j]->threads[k]->uuid, 36, 0);
        send(tmp->sock, "\" \"", 3, 0);
        send(tmp->sock, client->id, 36, 0);
        send(tmp->sock, "\" \"", 3, 0);
        send(tmp->sock,
        client->teams[i]->channels[j]->threads[k]->replies[n]->time,
        strlen(client->teams[i]->channels[j]->threads[k]->replies[n]->time), 0);
        send(tmp->sock, "\" \"", 3, 0);
        send(tmp->sock,
        client->teams[i]->channels[j]->threads[k]->replies[n]->msg,
        strlen(client->teams[i]->channels[j]->threads[k]->replies[n]->msg), 0);
        send(tmp->sock, "\"\n", 2, 0);
    }
}

void create_reply_command(struct client *c, char *buffer)
{
    char *r_uuid, *r_body, *tm, *c_uuid, *t_uuid, *u_uuid, *times;
    buffer += 12; buffer[strlen(buffer)] = '\0'; char *token = strtok(buffer
    , " "); r_uuid = token; token = strtok(NULL, " "); tm = token; token =
    strtok(NULL, " ");c_uuid = token; token = strtok(NULL, " "); t_uuid = token;
    token = strtok(NULL, " "); u_uuid = token; token = strtok(NULL, "\"");
    times = token; strtok(NULL, "\""); token = strtok(NULL, "\"");
    r_body = token; strtok(NULL, "\"");
    if (check_reply_error(c, tm, c_uuid, t_uuid) == 1) return;
    server_event_reply_created(t_uuid, u_uuid, r_body);
    int n = atoi(get_file_line(7, t_uuid, "threads/")); set_file_line(7, t_uuid
    , itoa(7 + 1), "threads/"); int i = find_t(tm, c); int j = find_c(c_uuid
    , c, tm); int k = find_th(c_uuid, c, tm, t_uuid);
    c->teams[i]->channels[j]->threads[k]->replies[n] =
    malloc(sizeof(struct reply));
    c->teams[i]->channels[j]->threads[k]->replies[n]->msg = strdup(r_body);
    c->teams[i]->channels[j]->threads[k]->replies[n]->uuid = strdup(r_uuid);
    c->teams[i]->channels[j]->threads[k]->replies[n]->time = strdup(times);
    c->teams[i]->channels[j]->threads[k]->replies[n]->c_uuid = strdup(c_uuid);
    put_r(c->teams[i]->channels[j]->threads[k]->replies[n], u_uuid, tm, t_uuid);
    send_info_reply(c, i, j, k, n);
}

void create_reply_file(struct reply *reply)
{
    int size = strlen("replies/") + strlen(reply->uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "replies/");
    strcat(path, reply->uuid);
    strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(reply->uuid, 1, strlen(reply->uuid), fd); fwrite("\n", 1, 1, fd);
    fwrite(reply->tm_uuid, 1, strlen(reply->tm_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->c_uuid, 1, strlen(reply->c_uuid), fd); fwrite("\n", 1, 1, fd);
    fwrite(reply->t_uuid, 1, strlen(reply->t_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->o_uuid, 1, strlen(reply->o_uuid), fd); fwrite("\n", 1, 1, fd);
    fwrite(reply->time, 1, strlen(reply->time), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->msg, 1, strlen(reply->msg), fd); fwrite("\n", 1, 1, fd);
    fclose (fd); free(path);
}
