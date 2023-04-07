/*
** EPITECH PROJECT, 2023
** create_reply.c
** File description:
** create_reply
*/

#include "server.h"

void put_s(struct reply *reply, char *uuid, char *tm_uuid, char *t_uuid)
{
    reply->t_uuid = strdup(t_uuid);
    reply->tm_uuid = strdup(tm_uuid);
    reply->o_uuid = strdup(uuid);
    create_reply_file(reply);
}

void create_reply_command(struct client *c, char *buffer)
{
    char *r_uuid; char *r_body; char *tm; char *c_uuid; char *t_uuid;
    buffer += 12; buffer[strlen(buffer)] = '\0'; char *u_uuid; char *times;
    char *token = strtok(buffer, " "); r_uuid = token;
    token = strtok(NULL, " "); tm = token; token = strtok(NULL, " ");
    c_uuid = token; token = strtok(NULL, " "); t_uuid = token;
    token = strtok(NULL, " "); u_uuid = token; token = strtok(NULL, "\"");
    times = token; strtok(NULL, "\""); token = strtok(NULL, "\"");
    r_body = token; strtok(NULL, "\"");
    server_event_reply_created(t_uuid, u_uuid, r_body);
    int n = atoi(get_file_line(7, t_uuid, "threads/"));
    set_file_line(7, t_uuid, itoa(7 + 1), "threads/");
    int i = find_t(tm, c); int j = find_c(c_uuid, c, tm);
    int k = find_th(c_uuid, c, tm, t_uuid);
    c->teams[i]->channels[j]->threads[k]->replies[n] =
    malloc(sizeof(struct reply));
    c->teams[i]->channels[j]->threads[k]->replies[n]->msg = strdup(r_body);
    c->teams[i]->channels[j]->threads[k]->replies[n]->uuid = strdup(r_uuid);
    c->teams[i]->channels[j]->threads[k]->replies[n]->time = strdup(times);
    c->teams[i]->channels[j]->threads[k]->replies[n]->c_uuid = strdup(c_uuid);
    put_s(c->teams[i]->channels[j]->threads[k]->replies[n], u_uuid, tm, t_uuid);
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
