/*
** EPITECH PROJECT, 2023
** list_command.c
** File description:
** list_command
*/

#include "client.h"

void list_teams(void)
{
    DIR *dir = opendir("./teams/");
    if (dir == NULL)
        return;
    struct dirent *file = readdir(dir);
    char *team_uuid = NULL, *team_name = NULL, *team_desc = NULL;
    while (file != NULL) {
        if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
            char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
            strncpy(uuid, file->d_name, 36);
            team_uuid = get_file_line(0, uuid, "./teams/");
            team_name = get_file_line(1, uuid, "./teams/");
            team_desc = get_file_line(2, uuid, "./teams/");
            client_print_teams(team_uuid, team_name, team_desc);
            free(team_uuid);
        }
        file = readdir(dir);
    }
    closedir(dir);
}

void list_channel(struct dirent *file, client_t *client)
{
    if (file->d_name[0] != '.' && strstr(file->d_name, ".txt")) {
        char *uuid = malloc(sizeof(char) * 37); memset(uuid, 0, 37);
        strncpy(uuid, file->d_name, 36);
        if (strcmp(get_file_line(3, uuid, "./channels/")
            , client->team_uuid) != 0) {
            free(uuid); return;
        }
        char *c_uuid = get_file_line(0, uuid, "./channels/");
        char *c_name = get_file_line(1, uuid, "./channels/");
        char *c_desc = get_file_line(2, uuid, "./channels/");
        client_team_print_channels(c_uuid, c_name, c_desc);
        free(c_uuid);
    }
}

void list_channels(client_t *client)
{
    if (check_if_file_exist(client->team_uuid, "./teams/") == 0) {
        client_error_unknown_team(client->team_uuid); return;
    }
    DIR *dir = opendir("./channels/");
    if (dir == NULL)
        return;
    struct dirent *file = readdir(dir);
    while (file != NULL) {
        list_channel(file, client);
        file = readdir(dir);
    }
    closedir(dir);
}

void list_command(client_t *client)
{
    if (client->context == 0)
        list_teams();
    if (client->context == 1)
        list_channels(client);
}
