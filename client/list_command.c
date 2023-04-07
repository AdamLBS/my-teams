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

void list_command(client_t *client)
{
    if (client->context == 0)
        list_teams();
}
