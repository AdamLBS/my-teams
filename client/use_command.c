/*
** EPITECH PROJECT, 2023
** use_command.c
** File description:
** use_command
*/

#include "client.h"

void set_contexts(client_t *client, char *thread_uuid, char *channel_uuid)
{
    if (channel_uuid != NULL) {
        if (client->channel_uuid != NULL) free(client->channel_uuid);
        client->channel_uuid = strdup(channel_uuid); client->context = 2;
    } if (thread_uuid != NULL) {
        if (client->thread_uuid != NULL) free(client->thread_uuid);
        client->thread_uuid = strdup(thread_uuid); client->context = 3;
    }
}

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
        if (client->team_uuid != NULL) free(client->team_uuid);
        client->team_uuid = strdup(team_uuid); client->context = 1;
    }
    strtok(NULL, "\""); channel_uuid = strtok(NULL, "\"");
    strtok(NULL, "\""); thread_uuid = strtok(NULL, "\"");
    set_contexts(client, thread_uuid, channel_uuid);
}
