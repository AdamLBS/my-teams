/*
** EPITECH PROJECT, 2023
** list_thread.c
** File description:
** list_thread
*/

#include "client.h"

void list_thread(struct dirent *file, client_t *client)
{
    if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, file->d_name, 36);
        if (strcmp(get_file_line(5, uuid, "./threads/")
            , client->team_uuid) != 0 || strcmp(get_file_line(6, uuid
            , "./threads/"), client->channel_uuid) != 0) {
            free(uuid); return;
        }
        char *t_uuid = get_file_line(0, uuid, "./threads/");
        char *t_u_uuid = get_file_line(1, uuid, "./threads/");
        char *t_name = get_file_line(3, uuid, "./threads/");
        char *t_desc = get_file_line(4, uuid, "./threads/");
        char *t_time = get_file_line(2, uuid, "./threads/");
        time_t currentTime = time(NULL);
        struct tm *timeInfos = localtime(&currentTime); struct tm tm;
        tm.tm_isdst = timeInfos->tm_isdst;
        strptime(t_time, "%a %b %d %H:%M:%S %Y", &tm); time_t t = mktime(&tm);
        client_channel_print_threads(t_uuid, t_u_uuid, t, t_name, t_desc);
        free(t_uuid); free(t_u_uuid); free(t_name); free(t_desc); free(t_time);
    }
}

void list_threads(client_t *client)
{
    if (check_if_file_exist(client->team_uuid, "./teams/") == 0) {
        client_error_unknown_team(client->team_uuid); return;
    }
    if (check_if_file_exist(client->channel_uuid, "./channels/") == 0) {
        client_error_unknown_channel(client->channel_uuid); return;
    }
    DIR *dir = opendir("./threads/");
    if (dir == NULL)
        return;
    struct dirent *file = readdir(dir);
    while (file != NULL) {
        list_thread(file, client);
        file = readdir(dir);
    }
    closedir(dir);
}
