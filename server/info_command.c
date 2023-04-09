/*
** EPITECH PROJECT, 2023
** info_command.c
** File description:
** info_command
*/

#include "server.h"

void send_error_info(struct client *client, char *nb)
{
    send(client->sock, "/info ERROR ", 12, 0);
    send(client->sock, nb, strlen(nb), 0);
    send(client->sock, "\n", 1, 0); return;
}

void info_team(struct client *client, char *team_uuid)
{
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
        send_error_info(client, "1"); return;
    }
    char *t_uuid = get_file_line_n(0, team_uuid, "./teams/");
    char *team_name = get_file_line_n(1, team_uuid, "./teams/");
    char *team_desc = get_file_line_n(2, team_uuid, "./teams/");
    send(client->sock, "/info 1 ", 8, 0);
    send(client->sock, t_uuid, 36, 0);
    send(client->sock, " \"", 2, 0);
    send(client->sock, team_name, strlen(team_name), 0);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, team_desc, strlen(team_desc), 0);
    send(client->sock, "\"\n", 2, 0);
    free(t_uuid); free(team_name); free(team_desc);
}

void info_channel(struct client *client, char *team_uuid, char *channel_uuid)
{
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
       send_error_info(client, "1"); return;
    }
    if (check_if_file_exist(channel_uuid, "./channels/") == 0) {
        send_error_info(client, "2"); return;
    }
    char *c_uuid = get_file_line_n(0, channel_uuid, "./channels/");
    char *c_name = get_file_line_n(1, channel_uuid, "./channels/");
    char *c_desc = get_file_line_n(2, channel_uuid, "./channels/");
    send(client->sock, "/info 2 ", 8, 0);
    send(client->sock, c_uuid, 36, 0);
    send(client->sock, " \"", 2, 0);
    send(client->sock, c_name, strlen(c_name), 0);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, c_desc, strlen(c_desc), 0);
    send(client->sock, "\"\n", 2, 0);
    free(c_uuid); free(c_name); free(c_desc);
}

void info_thread(struct client *client, char *team_uuid, char *channel_uuid
, char *thread_uuid)
{
    if (check_if_file_exist(team_uuid, "./teams/") == 0) {
       send_error_info(client, "1"); return;
    } if (check_if_file_exist(channel_uuid, "./channels/") == 0) {
        send_error_info(client, "2"); return;
    } if (check_if_file_exist(thread_uuid, "./threads/") == 0) {
        send_error_info(client, "3"); return;
    }
    char *t_uuid = get_file_line_n(0, thread_uuid, "./threads/"), *t_u_uuid =
    get_file_line_n(1, thread_uuid, "./threads/"), *t_name = get_file_line_n(3
    , thread_uuid, "./threads/"), *t_desc = get_file_line_n(4, thread_uuid
    , "./threads/"), *t_time = get_file_line_n(2, thread_uuid, "./threads/");
    send(client->sock, "/info 3 ", 8, 0); send(client->sock, t_uuid, 36, 0);
    send(client->sock, " ", 1, 0); send(client->sock, t_u_uuid, 36, 0);
    send(client->sock, " \"", 3, 0); free(t_uuid); free(t_u_uuid);
    send(client->sock, t_name, strlen(t_name), 0); free(t_name);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, t_desc, strlen(t_desc), 0); free(t_desc);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, t_time, strlen(t_time), 0); free(t_time);
    send(client->sock, "\"\n", 2, 0);
}

void info_command(struct client *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    str++;
    int context = atoi(strtok(str, " "));
    if (context == 1) {
        char *team_uuid = strtok(NULL, " ");
        info_team(client, team_uuid);
    } if (context == 2) {
        char *team_uuid = strtok(NULL, " ");
        char *channel_uuid = strtok(NULL, " ");
        info_channel(client, team_uuid, channel_uuid);
    } if (context == 3) {
        char *team_uuid = strtok(NULL, " ");
        char *channel_uuid = strtok(NULL, " ");
        char *thread_uuid = strtok(NULL, " ");
        info_thread(client, team_uuid, channel_uuid, thread_uuid);
    }
}
