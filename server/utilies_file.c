/*
** EPITECH PROJECT, 2023
** utilies_file.c
** File description:
** utilities_file
*/

#include "server.h"

int find_t(char *t_uuid, struct client *client)
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

int find_c(char *c_uuid, struct client *client, char *team_uuid)
{
    int i = 0;
    int j = find_t(team_uuid, client);
    while (i < client->teams[j]->nb_channels) {
        if (strcmp(client->teams[j]->channels[i]->uuid, c_uuid) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int find_th(char *c_uuid, struct client *client, char *tm_uuid, char *t_uuid)
{
    int i = 0;
    int j = find_t(tm_uuid, client);
    int k = find_c(c_uuid, client, tm_uuid);
    while (i < client->teams[j]->channels[k]->nb_threads) {
        if (strcmp(client->teams[j]->channels[k]->threads[i]->uuid, t_uuid)
            == 0) {
            return i;
        }
        i++;
    }
    return -1;
}
