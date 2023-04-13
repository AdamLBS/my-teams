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
    while (i <= client->nb_teams) {
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
    while (i <= client->teams[j]->nb_channels) {
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
    while (i <= client->teams[j]->channels[k]->nb_threads) {
        if (strcmp(client->teams[j]->channels[k]->threads[i]->uuid, t_uuid)
            == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int find_last_line(char *path)
{
    FILE *fd = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    int i = 0;
    while (getline(&line, &len, fd) != -1) {
        i++;
    }
    fclose(fd);
    return i;
}

void erase_line(char *to_find, char *dir, char *uuid)
{
    int size = strlen(dir) + strlen(uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    path = memset(path, '\0', size); strcpy(path, dir); strcat(path, uuid);
    strcat(path, ".txt");
    FILE *fd;
    fd = fopen(path, "r"); int id = 0;
    char *line = NULL; size_t len = 0; int i = 0;
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    while (getline(&line, &len, fd) != -1) {
        file[i] = line;
        if (strstr(line, to_find)) id = i;
        line = NULL;
        i++;
    }
    file[id] = strdup(""); fclose(fd); fd = fopen(path, "w");
    for (i = 0; file[i]; i++) fputs(file[i], fd);
    fclose(fd);
}
