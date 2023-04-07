/*
** EPITECH PROJECT, 2023
** create_channel.c
** File description:
** create_channel
*/

#include "server.h"

void create_channel_command(struct client *client, char *buffer)
{
    char *c_name; char *c_uuid; char *team_uuid; char *c_desc;
    buffer += 15; buffer[strlen(buffer)] = '\0';
    char *token = strtok(buffer, " ");
    team_uuid = token; token = strtok(NULL, " ");
    c_uuid = token; token = strtok(NULL, "\""); c_name = token;
    strtok(NULL, "\""); token = strtok(NULL, "\""); c_desc = token;
    server_event_channel_created(team_uuid, c_uuid, c_name);
    int n_channel = atoi(get_file_line(4, team_uuid, "teams/"));
    set_file_line(4, team_uuid, itoa(n_channel + 1), "teams/");
    int i = find_indice_team(team_uuid, client);
    client->teams[i]->nb_channels = n_channel + 1;
    client->teams[i]->channels[n_channel] = malloc(sizeof(struct channel));
    client->teams[i]->channels[n_channel]->name = strdup(c_name);
    client->teams[i]->channels[n_channel]->uuid = strdup(c_uuid);
    client->teams[i]->channels[n_channel]->desc = strdup(c_desc);
    client->teams[i]->channels[n_channel]->t_uuid = strdup(team_uuid);
    client->teams[i]->channels[n_channel]->threads =
    malloc(sizeof(struct thread *) * 100);
    create_c_file(c_uuid, c_name, team_uuid, c_desc);
}

void create_c_file(char *c_uuid, char *c_name, char *t_uuid, char *c_desc)
{
    int size = strlen("channels/") + strlen(c_uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "channels/");
    strcat(path, c_uuid); strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(c_uuid, 1, strlen(c_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(c_name, 1, strlen(c_name), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(c_desc, 1, strlen(c_desc), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(t_uuid, 1, strlen(t_uuid), fd);
    fwrite("\n0\n", 1, 3, fd);
    fclose (fd);
    free(path);
}
