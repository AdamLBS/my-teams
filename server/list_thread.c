/*
** EPITECH PROJECT, 2023
** list_thread.c
** File description:
** list_thread
*/

#include "server.h"

void list_thread(struct dirent *file, struct client *client
, char *team_uuid, char *channel_uuid)
{
    if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, file->d_name, 36); char *tmp = get_file_line_n(5, uuid
        , "./threads/"), *tmp2 = get_file_line_n(6, uuid, "./threads/");
        if (strcmp(tmp, team_uuid) != 0 || strcmp(tmp2, channel_uuid) != 0) {
            free(uuid); free(tmp); free(tmp2); return;
        } char *t_uuid = get_file_line_n(0, uuid, "./threads/"), *t_u_uuid =
        get_file_line_n(1, uuid, "./threads/"), *t_name = get_file_line_n(3
        , uuid, "./threads/"), *t_desc = get_file_line_n(4, uuid, "./threads/");
        char *t_time = get_file_line_n(2, uuid, "./threads/");
        send(client->sock, " \"", 3, 0); send(client->sock, t_uuid
        , strlen(t_uuid), 0);send(client->sock, "\" \"", 3, 0);send(client->sock
        , t_u_uuid, strlen(t_u_uuid), 0);send(client->sock, "\" \"", 3, 0);
        send(client->sock, t_name, strlen(t_name), 0);send(client->sock
        , "\" \"", 3, 0);send(client->sock, t_desc, strlen(t_desc), 0);
        send(client->sock, "\" \"", 3, 0);send(client->sock, t_time
        , strlen(t_time), 0);send(client->sock, "\"", 1, 0);free(t_uuid);
        free(t_u_uuid); free(t_name); free(t_desc); free(t_time);
        free(tmp); free(tmp2); free(uuid);
    }
}

void list_threads(struct client *client, char *team_uuid, char *channel_uuid)
{
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
        send(client->sock, "/list ERROR 1\n", 14, 0); return;
    }
    if (check_if_file_exist(channel_uuid, "./channels/") == 0) {
        send(client->sock, "/list ERROR 2\n", 14, 0); return;
    }
    DIR *dir = opendir("./threads/");
    if (dir == NULL)
        return;
    send(client->sock, "/list", 5, 0);
    struct dirent *file = readdir(dir);
    while (file != NULL) {
        list_thread(file, client, team_uuid, channel_uuid);
        file = readdir(dir);
    }
    send(client->sock, "\n", 1, 0);
    closedir(dir);
}
