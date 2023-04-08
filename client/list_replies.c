/*
** EPITECH PROJECT, 2023
** list_replies.c
** File description:
** list_replies
*/

#include "client.h"

reply_t list_reply(struct dirent *file, client_t *client)
{
    reply_t reply; reply.user_uuid = NULL;
    if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, file->d_name, 36); char *tmp = get_file_line(1, uuid
        , "./replies/"), *tmp2 = get_file_line(2, uuid, "./replies/"), *tmp3 =
        get_file_line(3, uuid, "./replies/"); if (strcmp(tmp
        , client->team_uuid) != 0 || strcmp(tmp2, client->channel_uuid) != 0 ||
            strcmp(tmp3, client->thread_uuid) != 0) {
            free(uuid); free(tmp); free(tmp2); free(tmp3); return reply;
        }
        reply.thread_uuid = get_file_line(3, uuid, "./replies/");
        reply.user_uuid = get_file_line(4, uuid, "./replies/");
        reply.body = get_file_line(6, uuid, "./replies/");
        char *r_time = get_file_line(5, uuid, "./replies/");
        time_t currentTime = time(NULL); struct tm *timeInfos =
        localtime(&currentTime), tm; tm.tm_isdst = timeInfos->tm_isdst;
        strptime(r_time, "%a %b %d %H:%M:%S %Y", &tm);
        reply.timestamp = mktime(&tm); free(uuid); free(tmp); free(tmp2);
        free(tmp3); free(r_time); return reply;
    } return reply;
}

int compare_time(const void *a, const void *b)
{
    reply_t *reply_a = (reply_t *)a;
    reply_t *reply_b = (reply_t *)b;
    return (int)(reply_a->timestamp - reply_b->timestamp);
}

void list_replies(client_t *client)
{
    DIR *dir = opendir("./replies/");
    if (dir == NULL) return;
    struct dirent *file = readdir(dir);
    reply_t *replies = malloc(sizeof(reply_t) * MAX_BODY_LENGTH);
    reply_t tmp; int i = 0;
    while (file != NULL) {
        tmp = list_reply(file, client);
        if (tmp.user_uuid != NULL) {
            replies[i] = tmp; i++;
        }
        file = readdir(dir);
    }
    closedir(dir); qsort(replies, i, sizeof(reply_t), compare_time);
    for (int j = 0; j < i; j++) {
        client_thread_print_replies(replies[j].thread_uuid
        , replies[j].user_uuid,replies[j].timestamp, replies[j].body);
        free(replies[j].user_uuid); free(replies[j].body);
        free(replies[j].thread_uuid);
    }
    free(replies);
}
