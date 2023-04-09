/*
** EPITECH PROJECT, 2023
** list_replies.c
** File description:
** list_replies
*/

#include "server.h"

replies_t list_reply(struct dirent *file, char data[3][37])
{
    replies_t reply; reply.user_uuid = NULL;
    if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, file->d_name, 36); char *tmp = get_file_line_n(1, uuid
        , "./replies/"), *tmp2 = get_file_line_n(2, uuid, "./replies/")
        , *tmp3 = get_file_line_n(3, uuid, "./replies/"); if (strcmp(tmp
        , data[0]) != 0 || strcmp(tmp2, data[1]) != 0 ||
            strcmp(tmp3, data[2]) != 0) {
            free(uuid); free(tmp); free(tmp2); free(tmp3); return reply;
        }
        reply.thread_uuid = get_file_line_n(3, uuid, "./replies/");
        reply.user_uuid = get_file_line_n(4, uuid, "./replies/");
        reply.body = get_file_line_n(6, uuid, "./replies/");
        reply.timestamp = get_file_line_n(5, uuid, "./replies/");
        free(uuid); free(tmp); free(tmp2);
        free(tmp3); return reply;
    } return reply;
}

int compare_time(const void *a, const void *b)
{
    replies_t *reply_a = (replies_t *)a;
    replies_t *reply_b = (replies_t *)b;
    return (int)(reply_a->timestamp - reply_b->timestamp);
}

int check_errors(struct client *client, char data[3][37])
{
    if (check_if_file_exist(data[0], "./teams/") == 0) {
        send(client->sock, "/list ERROR 1\n", 14, 0); return 0;
    }
    if (check_if_file_exist(data[1], "./channels/") == 0) {
        send(client->sock, "/list ERROR 2\n", 14, 0); return 0;
    }
    if (check_if_file_exist(data[2], "./threads/") == 0) {
        send(client->sock, "/list ERROR 3\n", 14, 0); return 0;
    }
    return 1;
}

void send_replies(struct client *client, replies_t *replies, int i)
{
    send(client->sock, "/list", 5, 0);
    for (int j = 0; j < i; j++) {
        send(client->sock, " \"", 3, 0);
        send(client->sock, replies[j].user_uuid, 36, 0);
        send(client->sock, "\" \"", 3, 0);
        send(client->sock, replies[j].thread_uuid, 36, 0);
        send(client->sock, "\" \"", 3, 0);
        send(client->sock, replies[j].body, strlen(replies[j].body), 0);
        send(client->sock, "\" \"", 3, 0);
        send(client->sock, replies[j].timestamp, strlen(replies[j].timestamp)
        , 0); send(client->sock, "\"", 1, 0);
        free(replies[j].user_uuid); free(replies[j].body);
        free(replies[j].thread_uuid); free(replies[j].timestamp);
    }
    send(client->sock, "\n", 1, 0);
}

void list_replies(struct client *client, char *team_uuid, char *channel_uuid
, char *thread_uuid)
{
    char data[3][37];
    strcpy(data[0], team_uuid); strcpy(data[1], channel_uuid);
    strcpy(data[2], thread_uuid);
    if (check_errors(client, data) == 0) return;
    DIR *dir = opendir("./replies/");
    if (dir == NULL) return;
    struct dirent *file = readdir(dir);
    replies_t *replies = malloc(sizeof(replies_t) * MAX_BODY_LENGTH);
    replies_t tmp; int i = 0;
    while (file != NULL) {
        tmp = list_reply(file, data);
        if (tmp.user_uuid != NULL) {
            replies[i] = tmp; i++;
        }
        file = readdir(dir);
    }
    closedir(dir); qsort(replies, i, sizeof(replies_t), compare_time);
    send_replies(client, replies, i);
    free(replies);
}
