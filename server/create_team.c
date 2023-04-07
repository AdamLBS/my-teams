/*
** EPITECH PROJECT, 2023
** create_team.c
** File description:
** create_team
*/

#include "server.h"

void create_team_command(struct client *client, char *buffer)
{
    char *team_name, *team_uuid, *team_desc;
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    buffer += 12; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token; token = strtok(NULL, "\""); team_name = token;
    strtok(NULL, "\""); token = strtok(NULL, "\""); team_desc = token;
    server_event_team_created(team_uuid, team_name, client->id);
    int nb_teams = atoi(get_file_line(3, client->id, "users/"));
    client->nb_teams = nb_teams + 1;
    set_file_line(3, client->id, itoa(nb_teams + 1), "users/");
    client->teams[nb_teams] = malloc(sizeof(struct team));
    client->teams[nb_teams]->name = strdup(team_name);
    client->teams[nb_teams]->uuid = strdup(team_uuid);
    client->teams[nb_teams]->desc = strdup(team_desc);
    client->teams[nb_teams]->channels = malloc(sizeof(struct channel *) * 100);
    create_team_file(team_uuid, team_name, team_desc);
}

void create_team_file(char *t_uuid, char *t_name, char *t_desc)
{
    int size = strlen("teams/") + strlen(t_uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "teams/");
    strcat(path, t_uuid);
    strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(t_uuid, 1, strlen(t_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(t_name, 1, strlen(t_name), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(t_desc, 1, strlen(t_desc), fd);
    fwrite("\n0\n0\n", 1, 5, fd);
    fclose (fd);
    free(path);
}
