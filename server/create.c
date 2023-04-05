/*
** EPITECH PROJECT, 2023
** create.c
** File description:
** create
*/

#include "server.h"

void create_team_command(struct client *client, char *buffer)
{
    char *team_name; char *team_desc; char *team_uuid;
    buffer += 12; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token;
    token = strtok(NULL, " ");
    team_name = token; token = strtok(NULL, ""); team_desc = token;
    server_event_team_created(team_uuid, team_name, client->id);
}