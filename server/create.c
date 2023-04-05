/*
** EPITECH PROJECT, 2023
** create.c
** File description:
** create
*/

#include "server.h"

void create_team_command(struct client *client, char *buffer)
{
    char *team_name; char *team_uuid;
    buffer += 12; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token;
    token = strtok(NULL, " ");
    team_name = token;
    server_event_team_created(team_uuid, team_name, client->id);
}

void create_channel_command(char *buffer)
{
    char *channel_name; char *channel_uuid; char *team_uuid;
    buffer += 15; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token;
    token = strtok(NULL, " ");
    channel_uuid = token;
    token = strtok(NULL, " ");
    channel_name = token;
    token = strtok(NULL, " ");
    server_event_channel_created(team_uuid, channel_uuid, channel_name);
}
