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
    int n_channel = atoi(get_file_line(4, team_uuid, "teams/"));
    set_file_line(4, team_uuid, itoa(n_channel + 1), "teams/");
    int i = find_indice_team(team_uuid, client);
    client->teams[i]->nb_channels = n_channel + 1;
    client->teams[i]->channels[n_channel] = malloc(sizeof(struct channel));
    client->teams[i]->channels[n_channel]->name = strdup(c_name);
    client->teams[i]->channels[n_channel]->uuid = strdup(c_uuid);
    client->teams[i]->channels[n_channel]->desc = strdup(c_desc);
    client->teams[i]->channels[n_channel]->t_uuid = strdup(team_uuid);
    client->teams[i]->channels[n_channel]->threads = malloc(sizeof(struct thread *) * 100);
    create_c_file(c_uuid, c_name, team_uuid, c_desc);
}

void create_thread_command(struct client *client, char *buffer)
{
    char *t_name; char *t_uuid; char *c_uuid; char *t_body; char *tm_uuid;
    buffer += 15; buffer[strlen(buffer)] = '\0'; char *u_uuid;
    char *token = strtok(buffer, " "); tm_uuid = token;
    token = strtok(NULL, " "); c_uuid = token; token = strtok(NULL, " ");
    u_uuid = token; token = strtok(NULL, " ");
    t_uuid = token; token = strtok(NULL, "\""); t_name = token;
    strtok(NULL, "\""); token = strtok(NULL, "\""); t_body = token;
    server_event_thread_created(c_uuid, t_uuid, u_uuid, t_name, t_body);
    int nb_threads = atoi(get_file_line(4, c_uuid, "channels/"));
    set_file_line(4, c_uuid, itoa(nb_threads + 1), "channels/");
    int i = find_indice_team(tm_uuid, client);
    int j = find_indice_channel(c_uuid, client, tm_uuid);
    client->teams[i]->channels[j]->threads[nb_threads] = malloc(sizeof(struct thread));
    client->teams[i]->channels[j]->threads[nb_threads]->name = strdup(t_name);
    client->teams[i]->channels[j]->threads[nb_threads]->uuid = strdup(t_uuid);
    client->teams[i]->channels[j]->threads[nb_threads]->body = strdup(t_body);
    client->teams[i]->channels[j]->threads[nb_threads]->c_uuid = strdup(c_uuid);
    create_thread_file(client->teams[i]->channels[j]->threads[nb_threads]);
}