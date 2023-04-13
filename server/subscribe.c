/*
** EPITECH PROJECT, 2023
** subscribe.c
** File description:
** subscribe
*/

#include "server.h"

void subscribe_command(struct client *cli, char *buffer)
{
    char *team_uuid;
    buffer += 11;
    char *token = strtok(buffer, "\"");
    team_uuid = clean_text(token);
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
        send(cli->sock, "313\n", 4, 0);
        return;
    }
    if (check_permissions(cli, team_uuid) == 0) {
        send(cli->sock, "102\n", 4, 0);
        return;
    }
    write_new_member(cli->id, team_uuid);
    server_event_user_subscribed(team_uuid, cli->id);
    load_teams(cli, team_uuid);
    send(cli->sock, "901\n", 4, 0);
}

void unsubscribe_command(struct client *cli, char *buffer)
{
    char *team_uuid;
    buffer += 13;
    char *token = strtok(buffer, "\"");
    team_uuid = clean_text(token);
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
        send(cli->sock, "313\n", 4, 0);
        return;
    }
    if (check_permissions(cli, team_uuid) == 1) {
        send(cli->sock, "102\n", 4, 0);
        return;
    }
    erase_line(cli->id, "./teams/", team_uuid);
    erase_line(team_uuid, "./users/", cli->id);
    remove_team_from_struct(team_uuid, cli);
    server_event_user_unsubscribed(team_uuid, cli->id);
    send(cli->sock, "902\n", 4, 0);
}

void remove_team_from_struct(char *uuid, struct client *cli)
{
    struct team **tmp = malloc(sizeof(struct team *) * 100);
    for (int i = 0, j = 0; i <= cli->nb_teams; i++) {
        if (strcmp(cli->teams[i]->uuid, uuid) != 0) {
            tmp[j] = cli->teams[i];
            j++;
        }
    }
    for (int i = 0; i <= cli->nb_teams; i++) {
        free(cli->teams[i]->uuid);
        free(cli->teams[i]->name);
        free(cli->teams[i]->desc);
        free (cli->teams[i]);
    }
    free(cli->teams);
    cli->nb_teams--;
    char *nb = itoa(cli->nb_teams + 1);
    set_file_line(3, cli->id, nb, "./users/");
    cli->teams = malloc(sizeof(struct team *) * 100);
    for (int i = 0; i <= cli->nb_teams; i++) {
        cli->teams[i] = malloc(sizeof(struct team));
        cli->teams[i]->uuid = strdup(tmp[i]->uuid);
        cli->teams[i]->name = strdup(tmp[i]->name);
        cli->teams[i]->desc = strdup(tmp[i]->desc);
        cli->teams[i]->nb_channels = tmp[i]->nb_channels;
        cli->teams[i]->channels = malloc(sizeof(struct channel *) * 100);
        free(tmp[i]);
    }
    free(tmp);
}
