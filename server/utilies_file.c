/*
** EPITECH PROJECT, 2023
** utilies_file.c
** File description:
** utilities_file
*/

#include "server.h"

int find_indice_team(char *t_uuid, struct client *client)
{
    int i = 0;
    while (i < client->nb_teams) {
        if (strcmp(client->teams[i]->uuid, t_uuid) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int find_indice_channel(char *c_uuid, struct client *client, char *team_uuid)
{
    int i = 0;
    int j = find_indice_team(team_uuid, client);
    printf("j = %d\n", j);
    while (i < client->teams[j]->nb_channels) {
        if (strcmp(client->teams[j]->channels[i]->uuid, c_uuid) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}