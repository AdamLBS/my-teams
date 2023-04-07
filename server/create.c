/*
** EPITECH PROJECT, 2023
** create.c
** File description:
** create
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

void create_channel_command(struct client *client, char *buffer)
{
    char *c_name; char *c_uuid; char *team_uuid; char *c_desc;
    buffer += 15; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token; token = strtok(NULL, " ");
    c_uuid = token; token = strtok(NULL, "\""); c_name = token;
    strtok(NULL, "\""); token = strtok(NULL, "\""); c_desc = token;
    server_event_channel_created(team_uuid, c_uuid, c_name);
    int nb_channels = atoi(get_file_line(4, team_uuid, "teams/"));
    set_file_line(4, team_uuid, itoa(nb_channels + 1), "teams/"); int i = 0;
    while (i < client->nb_teams) {
        if (strcmp(client->teams[i]->uuid, team_uuid) == 0) break;
        i++;
    }
    client->teams[i]->channels[nb_channels] = malloc(sizeof(struct channel));
    client->teams[i]->channels[nb_channels]->name = strdup(c_name);
    client->teams[i]->channels[nb_channels]->uuid = strdup(c_uuid);
    client->teams[i]->channels[nb_channels]->desc = strdup(c_desc);
    client->teams[i]->channels[nb_channels]->t_uuid = strdup(team_uuid);
    create_c_file(c_uuid, c_name, team_uuid, c_desc);
}
