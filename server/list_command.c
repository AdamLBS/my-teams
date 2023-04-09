/*
** EPITECH PROJECT, 2023
** list_command.c
** File description:
** list_command
*/

#include "server.h"

void list_teams(struct client *client)
{
    DIR *dir = opendir("./teams/");
    if (dir == NULL) return;
    send(client->sock, "/list", 5, 0); struct dirent *file = readdir(dir);
    char *team_uuid = NULL, *team_name = NULL, *team_desc = NULL;
    while (file != NULL) {
        if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
            char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
            strncpy(uuid, file->d_name, 36); team_uuid = get_file_line_n(0
            , uuid, "./teams/");    team_name = get_file_line_n(1, uuid
            , "./teams/"); team_desc = get_file_line_n(2, uuid, "./teams/");
            send(client->sock, " \"", 2, 0); send(client->sock, team_uuid
            , 36, 0); send(client->sock, "\" \"", 3, 0); send(client->sock
            , team_name, strlen(team_name), 0); send(client->sock, "\" \"", 3
            , 0); send(client->sock, team_desc, strlen(team_desc), 0);
            send(client->sock, "\"", 1, 0);
            free(team_uuid); free(team_name); free(team_desc); free(uuid);
        }
        file = readdir(dir);
    }
    closedir(dir); send(client->sock, "\n", 1, 0);
}

void list_channel(struct dirent *file, struct client *client, char *team_uuid)
{
    if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, file->d_name, 36);
        char *tmp = get_file_line_n(3, uuid, "./channels/");
        if (strcmp(tmp, team_uuid) != 0) {
            free(uuid); free(tmp); return;
        }
        char *c_uuid = get_file_line_n(0, uuid, "./channels/");
        char *c_name = get_file_line_n(1, uuid, "./channels/");
        char *c_desc = get_file_line_n(2, uuid, "./channels/");
        send(client->sock, " \"", 2, 0);
        send(client->sock, c_uuid, strlen(c_uuid), 0);
        send(client->sock, "\" \"", 3, 0);
        send(client->sock, c_name, strlen(c_name), 0);
        send(client->sock, "\" \"", 3, 0);
        send(client->sock, c_desc, strlen(c_desc), 0);
        send(client->sock, "\"", 1, 0);
        free(c_uuid); free(c_name); free(c_desc); free(uuid); free(tmp);
    }
}

void list_channels(struct client *client, char *team_uuid)
{
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
        send(client->sock, "/list ERROR 1\n", 14, 0); return;
    }
    DIR *dir = opendir("./channels/");
    if (dir == NULL)
        return;
    send(client->sock, "/list", 5, 0);
    struct dirent *file = readdir(dir);
    while (file != NULL) {
        list_channel(file, client, team_uuid);
        file = readdir(dir);
    }
    closedir(dir); send(client->sock, "\n", 1, 0);
}

void list_command(struct client *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    str++;
    int context = atoi(str);
    if (context == 0) {
        list_teams(client);
    } if (context == 1) {
        strtok(str, " ");
        list_channels(client, strtok(NULL, " "));
    } if (context == 2) {
        strtok(str, " ");
        char *team = strtok(NULL, " ");
        char *channel = strtok(NULL, " ");
        list_threads(client, team, channel);
    } if (context == 3) {
        strtok(str, " ");
        char *team = strtok(NULL, " ");
        char *channel = strtok(NULL, " ");
        char *thread = strtok(NULL, " ");
        list_replies(client, team, channel, thread);
    }
}
