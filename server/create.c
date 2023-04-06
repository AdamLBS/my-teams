/*
** EPITECH PROJECT, 2023
** create.c
** File description:
** create
*/

#include "server.h"

void create_team_command(struct client *client, char *buffer)
{
    char *team_name; char *team_uuid; char *team_desc;
    buffer += 12; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token;
    token = strtok(NULL, " ");
    team_name = token;
    token = strtok(NULL, " ");
    team_desc = token;
    server_event_team_created(team_uuid, team_name, client->id);
}

void create_channel_command(char *buffer)
{
    char *c_name; char *c_uuid; char *team_uuid; char *c_desc;
    buffer += 15; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token; token = strtok(NULL, " ");
    c_uuid = token; token = strtok(NULL, " ");
    c_name = token; token = strtok(NULL, " ");
    c_desc = token; token = strtok(NULL, " ");
    printf("Channel created: %s, %s\n", c_name, c_desc);
    server_event_channel_created(team_uuid, c_uuid, c_name);
}
