/*
** EPITECH PROJECT, 2023
** create_file.c
** File description:
** create_file
*/

#include "server.h"

int check_thread_error(struct client *client, char *t_name, char *team_uuid
, char *t_uuid)
{
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
        send(client->sock, "311\n", 4, 0); return 1;
    }
    if (check_if_file_exist(t_uuid, "./threads/") == 1) {
        send(client->sock, "331\n", 4, 0); return 1;
    }
    if (check_if_title_exist(t_name, "./threads/") == 1) {
        send(client->sock, "332\n", 4, 0); return 1;
    }
    if (check_permissions(client, team_uuid) == 1) {
        send(client->sock, "101\n", 4, 0); return 1;
    }
    return 0;
}

int check_thread_error2(struct client *client, char *c_uuid)
{
    if (check_if_file_exist(c_uuid, "./channels/") == 0) {
        send(client->sock, "321\n", 4, 0); return 1;
    }
    return 0;
}

void send_info_thread(struct client *client, int i, int j, int n)
{
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (check_permissions(tmp, client->teams[i]->uuid) != 1) {
            send(tmp->sock, "931 \"", 5, 0);
            send(tmp->sock, client->teams[i]->channels[j]->threads[n]->uuid, 36
            , 0); send(tmp->sock, "\" \"", 3, 0);
            send(tmp->sock, client->id, 36, 0);
            send(tmp->sock, "\" \"", 3, 0);
            send(tmp->sock, client->teams[i]->channels[j]->threads[n]->time,
            strlen(client->teams[i]->channels[j]->threads[n]->time), 0);
            send(tmp->sock, "\" \"", 3, 0);
            send(tmp->sock, client->teams[i]->channels[j]->threads[n]->name,
            strlen(client->teams[i]->channels[j]->threads[n]->name), 0);
            send(tmp->sock, "\" \"", 3, 0);
            send(tmp->sock, client->teams[i]->channels[j]->threads[n]->body,
            strlen(client->teams[i]->channels[j]->threads[n]->body), 0);
            send(tmp->sock, "\"\n", 2, 0);
        }
    }
}

void create_thread_command(struct client *client, char *buffer)
{
    char *t_name, *t_uuid, *c_uuid, *t_body, *tm_uuid, *u_uuid, *times;
    buffer += 14; buffer[strlen(buffer)] = '\0'; char *token = strtok(buffer
    , " "); tm_uuid = token; token = strtok(NULL, " "); c_uuid = token; token =
    strtok(NULL, " ");u_uuid = token; token = strtok(NULL, " "); t_uuid = token;
    token = strtok(NULL, "\""); times = token; strtok(NULL, "\"");
    token = strtok(NULL, "\""); t_name = token; strtok(NULL, "\"");
    token = strtok(NULL, "\""); t_body = token;
    if (check_thread_error(client, t_name, tm_uuid, t_uuid) == 1) return;
    if (check_thread_error2(client, c_uuid) == 1) return;
    server_event_thread_created(c_uuid, t_uuid, u_uuid, t_name, t_body);
    int n = atoi(get_file_line(4, c_uuid, "channels/"));set_file_line(4, c_uuid,
    itoa(n + 1), "channels/"); int i = find_t(tm_uuid, client), j =
    find_c(c_uuid, client, tm_uuid);client->teams[i]->channels[j]->threads[n] =
    malloc(sizeof(struct thread)); client->teams[i]->channels[j]->nb_threads =
    n + 1; client->teams[i]->channels[j]->threads[n]->name = strdup(t_name);
    client->teams[i]->channels[j]->threads[n]->uuid = strdup(t_uuid);
    client->teams[i]->channels[j]->threads[n]->body = strdup(t_body);
    client->teams[i]->channels[j]->threads[n]->c_uuid = strdup(c_uuid);
    put_s(client->teams[i]->channels[j]->threads[n], times, tm_uuid, u_uuid);
    send_info_thread(client, i, j, n);
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
