/*
** EPITECH PROJECT, 2023
** subscribed.c
** File description:
** subscribed
*/

#include "server.h"

void send_infos_subscribed(struct client *client, char **teams)
{
    send(client->sock, "/list", 5, 0);
    for (int j = 0; teams[j]; j++) {
        char *team_uuid = get_file_line_n(0, teams[j], "./teams/");
        char *team_name = get_file_line_n(1, teams[j], "./teams/");
        char *team_desc = get_file_line_n(2, teams[j], "./teams/");
        send(client->sock, " \"", 2, 0);
        send(client->sock, team_uuid, 36, 0);
        send(client->sock, "\" \"", 3, 0);
        send(client->sock, team_name, strlen(team_name), 0);
        send(client->sock, "\" \"", 3, 0);
        send(client->sock, team_desc, strlen(team_desc), 0);
        send(client->sock, "\"", 1, 0);
        free(team_uuid); free(team_name); free(team_desc); free(teams[j]);
    }
    send(client->sock, "\n", 1, 0);
    free(teams);
}

void list_teams_subribed(struct client *client, char *buffer)
{
    char *path = malloc(sizeof(char) * (strlen(client->id) + 14));
    strcpy(path, "./users/"); strcat(path, client->id); strcat(path, ".txt");
    char **teams = malloc(sizeof(char *) * 100);
    FILE *file = fopen(path, "r");
    char *line = NULL;
    int i = 0;
    size_t len = 0;
    while (getline(&line, &len, file) != -1) {
        if (i < 4) {
            i++; continue;
        }
        line[strlen(line) - 1] = '\0';
        teams[i - 4] = malloc(sizeof(char) * (strlen(line) + 1));
        strcpy(teams[i - 4], line);
        i++;
    }
    fclose(file);teams[i - 4] = NULL; free(path);
    send_infos_subscribed(client, teams);
}

void subscribed_command(struct client *cli, char *buffer)
{
    if (strcmp(buffer, "/subscribed") == 0) {
        list_teams_subribed(cli, buffer);
        return;
    }
}
