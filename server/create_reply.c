/*
** EPITECH PROJECT, 2023
** create_reply.c
** File description:
** create_reply
*/

#include "server.h"

void create_reply_command(struct client *client, char *buffer)
{
    char *r_uuid; char *r_body; char *tm_uuid; char *c_uuid; char *t_uuid;
    buffer += 12; buffer[strlen(buffer)] = '\0'; char *u_uuid; char *times;
    char *token = strtok(buffer, " "); r_uuid = token;
    token = strtok(NULL, " "); tm_uuid = token; token = strtok(NULL, " ");
    c_uuid = token; token = strtok(NULL, " "); t_uuid = token; token = strtok(NULL, " ");
    u_uuid = token; token = strtok(NULL, "\""); times = token; strtok(NULL, "\"");
    token = strtok(NULL, "\""); r_body = token;
    strtok(NULL, "\"");
    server_event_reply_created(t_uuid, u_uuid, r_body);
    int n = atoi(get_file_line(7, t_uuid, "threads/"));
    set_file_line(7, t_uuid, itoa(7 + 1), "threads/");
    int i = find_indice_team(tm_uuid, client);
    int j = find_indice_channel(c_uuid, client, tm_uuid);
    int k = find_indice_thread(c_uuid, client, tm_uuid, t_uuid);
    client->teams[i]->channels[j]->threads[k]->replies[n] = malloc(sizeof(struct reply));
    client->teams[i]->channels[j]->threads[k]->replies[n]->msg = strdup(r_body);
    client->teams[i]->channels[j]->threads[k]->replies[n]->uuid = strdup(r_uuid);
    client->teams[i]->channels[j]->threads[k]->replies[n]->time = strdup(times);
    client->teams[i]->channels[j]->threads[k]->replies[n]->c_uuid = strdup(c_uuid);
    client->teams[i]->channels[j]->threads[k]->replies[n]->t_uuid = strdup(t_uuid);
    client->teams[i]->channels[j]->threads[k]->replies[n]->tm_uuid = strdup(tm_uuid);
    client->teams[i]->channels[j]->threads[k]->replies[n]->o_uuid = strdup(u_uuid);
    create_reply_file(client->teams[i]->channels[j]->threads[k]->replies[n]);
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
    fwrite(reply->uuid, 1, strlen(reply->uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->tm_uuid, 1, strlen(reply->tm_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->c_uuid, 1, strlen(reply->c_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->t_uuid, 1, strlen(reply->t_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->o_uuid, 1, strlen(reply->o_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->time, 1, strlen(reply->time), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(reply->msg, 1, strlen(reply->msg), fd);
    fwrite("\n", 1, 1, fd);
    fclose (fd);
    free(path);
}