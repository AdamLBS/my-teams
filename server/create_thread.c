/*
** EPITECH PROJECT, 2023
** create_file.c
** File description:
** create_file
*/

#include "server.h"

void put_s(struct thread *thread, char *time, char *t_uuid, char *o_uuid)
{
    thread->o_uuid = strdup(o_uuid);
    thread->t_uuid = strdup(t_uuid);
    thread->time = strdup(time);
    thread->replies = malloc(sizeof(struct reply *) * 100);
    create_thread_file(thread);
}

void create_thread_command(struct client *client, char *buffer)
{
    char *t_name; char *t_uuid; char *c_uuid; char *t_body; char *tm_uuid;
    buffer += 14; buffer[strlen(buffer)] = '\0'; char *u_uuid; char *times;
    char *token = strtok(buffer, " "); tm_uuid = token;
    token = strtok(NULL, " "); c_uuid = token; token = strtok(NULL, " ");
    u_uuid = token; token = strtok(NULL, " "); t_uuid = token;
    token = strtok(NULL, "\""); times = token; strtok(NULL, "\"");
    token = strtok(NULL, "\""); t_name = token; strtok(NULL, "\"");
    token = strtok(NULL, "\""); t_body = token;
    server_event_thread_created(c_uuid, t_uuid, u_uuid, t_name, t_body);
    int n = atoi(get_file_line(4, c_uuid, "channels/"));
    set_file_line(4, c_uuid, itoa(n + 1), "channels/");
    int i = find_t(tm_uuid, client); int j = find_c(c_uuid, client, tm_uuid);
    client->teams[i]->channels[j]->threads[n] =
    malloc(sizeof(struct thread));
    client->teams[i]->channels[j]->nb_threads = n + 1;
    client->teams[i]->channels[j]->threads[n]->name = strdup(t_name);
    client->teams[i]->channels[j]->threads[n]->uuid = strdup(t_uuid);
    client->teams[i]->channels[j]->threads[n]->body = strdup(t_body);
    client->teams[i]->channels[j]->threads[n]->c_uuid = strdup(c_uuid);
    put_s(client->teams[i]->channels[j]->threads[n], times, tm_uuid, u_uuid);
}

void create_thread_file(struct thread *thread)
{
    int size = strlen("threads/") + strlen(thread->uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "threads/");
    strcat(path, thread->uuid);
    strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(thread->uuid, 1, strlen(thread->uuid), fd); fwrite("\n", 1, 1, fd);
    fwrite(thread->o_uuid, 1, strlen(thread->o_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(thread->time, 1, strlen(thread->time), fd); fwrite("\n", 1, 1, fd);
    fwrite(thread->name, 1, strlen(thread->name), fd); fwrite("\n", 1, 1, fd);
    fwrite(thread->body, 1, strlen(thread->body), fd); fwrite("\n", 1, 1, fd);
    fwrite(thread->t_uuid, 1, strlen(thread->t_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(thread->c_uuid, 1, strlen(thread->c_uuid), fd);
    fwrite("\n0\n", 1, 3, fd); fclose (fd); free(path);
}
