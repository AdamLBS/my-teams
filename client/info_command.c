/*
** EPITECH PROJECT, 2023
** info_command.c
** File description:
** info_command
*/

#include "client.h"

void info_team(client_t *client)
{
    if (check_if_file_exist(client->team_uuid, "./teams/") == 0) {
        client_error_unknown_team(client->team_uuid);
        return;
    }
    char *team_uuid = get_file_line(0, client->team_uuid, "./teams/");
    char *team_name = get_file_line(1, client->team_uuid, "./teams/");
    char *team_desc = get_file_line(2, client->team_uuid, "./teams/");
    client_print_team(team_uuid, team_name, team_desc);
}

void info_channel(client_t *client)
{
    if (check_if_file_exist(client->channel_uuid, "./channels/") == 0) {
        client_error_unknown_channel(client->channel_uuid);
        return;
    }
    char *c_uuid = get_file_line(0, client->channel_uuid, "./channels/");
    char *c_name = get_file_line(1, client->channel_uuid, "./channels/");
    char *c_desc = get_file_line(2, client->channel_uuid, "./channels/");
    client_print_channel(c_uuid, c_name, c_desc);
}

void info_command(client_t *client)
{
    if (client->context == 0)
        send(client->sock, "/users\n", 7, 0);
    if (client->context == 1)
        info_team(client);
    if (client->context == 2)
        info_channel(client);
}
