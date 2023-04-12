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
        send(cli->sock, "311\n", 4, 0);
    }
    write_new_member(cli->id, team_uuid);
    server_event_user_subscribed(team_uuid, cli->id);
    send(cli->sock, "901\n", 4, 0);
}

void unsubcribe_command(struct client *cli, char *buffer)
{
    char *team_uuid;
    buffer += 13;
    char *token = strtok(buffer, "\"");
    team_uuid = clean_text(token);
    write_new_member(cli->id, team_uuid);
}