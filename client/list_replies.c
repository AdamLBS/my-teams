/*
** EPITECH PROJECT, 2023
** list_replies.c
** File description:
** list_replies
*/

#include "client.h"

void list_reply(struct dirent *file, client_t *client)
{
    if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, file->d_name, 36);
        if (strcmp(get_file_line(1, uuid, "./replies/")
            , client->team_uuid) != 0 || strcmp(get_file_line(2, uuid
            , "./replies/"), client->channel_uuid) != 0 ||
            strcmp(get_file_line(3, uuid, "./replies/")
            , client->thread_uuid) != 0) {
            free(uuid); return;
        }
        char *r_t_uuid = get_file_line(3, uuid, "./replies/");
        char *r_u_uuid = get_file_line(4, uuid, "./replies/");
        char *r_desc = get_file_line(6, uuid, "./replies/");
        char *r_time = get_file_line(5, uuid, "./replies/");
        time_t currentTime = time(NULL); struct tm *timeInfos =
        localtime(&currentTime), tm; tm.tm_isdst = timeInfos->tm_isdst;
        strptime(r_time, "%a %b %d %H:%M:%S %Y", &tm);time_t t = mktime(&tm);
        client_thread_print_replies(r_t_uuid, r_u_uuid, t, r_desc);
        free(r_t_uuid); free(r_u_uuid); free(r_desc); free(r_time);
    }
}

void list_replies(client_t *client)
{
    if (check_if_file_exist(client->team_uuid, "./teams/") == 0) {
        client_error_unknown_team(client->team_uuid); return;
    }
    if (check_if_file_exist(client->channel_uuid, "./channels/") == 0) {
        client_error_unknown_channel(client->channel_uuid); return;
    }
    if (check_if_file_exist(client->thread_uuid, "./threads/") == 0) {
        client_error_unknown_thread(client->thread_uuid); return;
    }
    DIR *dir = opendir("./replies/");
    if (dir == NULL)
        return;
    struct dirent *file = readdir(dir);
    while (file != NULL) {
        list_reply(file, client);
        file = readdir(dir);
    }
    closedir(dir);
}
