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
    free(team_uuid); free(team_name); free(team_desc);
}

void info_channel(client_t *client)
{
    if (check_if_file_exist(client->team_uuid, "./teams/") == 0) {
        client_error_unknown_team(client->team_uuid);
        return;
    }
    if (check_if_file_exist(client->channel_uuid, "./channels/") == 0) {
        client_error_unknown_channel(client->channel_uuid);
        return;
    }
    char *c_uuid = get_file_line(0, client->channel_uuid, "./channels/");
    char *c_name = get_file_line(1, client->channel_uuid, "./channels/");
    char *c_desc = get_file_line(2, client->channel_uuid, "./channels/");
    client_print_channel(c_uuid, c_name, c_desc);
    free(c_uuid); free(c_name); free(c_desc);
}

void info_thread(client_t *client)
{
    if (check_if_file_exist(client->team_uuid, "./teams/") == 0) {
        client_error_unknown_team(client->team_uuid); return;
    }
    if (check_if_file_exist(client->channel_uuid, "./channels/") == 0) {
        client_error_unknown_channel(client->channel_uuid); return;
    }
    if (check_if_file_exist(client->thread_uuid, "./threads/") == 0) {
        client_error_unknown_thread(client->thread_uuid); return;
    }
    char *t_uuid = get_file_line(0, client->thread_uuid, "./threads/");
    char *t_u_uuid = get_file_line(1, client->thread_uuid, "./threads/");
    char *t_name = get_file_line(3, client->thread_uuid, "./threads/");
    char *t_desc = get_file_line(4, client->thread_uuid, "./threads/");
    char *t_time = get_file_line(2, client->thread_uuid, "./threads/");
    time_t currentTime = time(NULL);
    struct tm *timeInfos = localtime(&currentTime); struct tm tm;
    tm.tm_isdst = timeInfos->tm_isdst;
    strptime(t_time, "%a %b %d %H:%M:%S %Y", &tm); time_t t = mktime(&tm);
    client_print_thread(t_uuid, t_u_uuid, t, t_name, t_desc);
    free(t_uuid); free(t_u_uuid); free(t_name); free(t_desc); free(t_time);
}

void info_command(client_t *client)
{
    if (client->context == 0)
        send(client->sock, "/users\n", 7, 0);
    if (client->context == 1)
        info_team(client);
    if (client->context == 2)
        info_channel(client);
    if (client->context == 3)
        info_thread(client);
}
