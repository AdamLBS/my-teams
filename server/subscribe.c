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
    // todo: remove team struct from user
    server_event_user_unsubscribed(team_uuid, cli->id);
    send(cli->sock, "902\n", 4, 0);
}
