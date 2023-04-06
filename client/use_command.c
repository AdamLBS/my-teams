/*
** EPITECH PROJECT, 2023
** use_command.c
** File description:
** use_command
*/

#include "client.h"

void use_command(client_t *client, char *buffer)
{
    if (strcmp(buffer, "/use") == 0) {
        client->context = 0; return;
    }
    char *str = strchr(buffer, '"');
    if (str != NULL && str[1] != '\0') str++;
    else
        return;
    if (str[strlen(str) - 1] == '"') str[strlen(str) - 1] = '\0';
    char *team_uuid = NULL, *channel_uuid = NULL, *thread_uuid = NULL;
    team_uuid = strtok(str, "\""); client->context = 0;
    if (team_uuid != NULL) {
        client->team_uuid = strdup(team_uuid); client->context = 1;
    }
    channel_uuid = strtok(NULL, "\""); thread_uuid = strtok(NULL, "\"");
    if (channel_uuid != NULL) {
        client->channel_uuid = strdup(channel_uuid); client->context = 2;
    }
    if (thread_uuid != NULL) {
        client->thread_uuid = strdup(thread_uuid); client->context = 3;
    }
}
