/*
** EPITECH PROJECT, 2023
** info_command_receive.c
** File description:
** info_command_receive
*/

#include "client.h"

void info_team(char *buffer)
{
    char *str = strchr(buffer, ' ');
    str++; str++;
    char *team_uuid = strtok(str, " ");
    char *team_name = strtok(NULL, "\"");
    strtok(NULL, "\"");
    char *team_desc = strtok(NULL, "\"");
    client_print_team(team_uuid, team_name, team_desc);
}

void info_channel(char *buffer)
{
    char *str = strchr(buffer, ' ');
    str++; str++;
    char *c_uuid = strtok(str, " ");
    char *c_name = strtok(NULL, "\"");
    strtok(NULL, "\"");
    char *c_desc = strtok(NULL, "\"");
    client_print_channel(c_uuid, c_name, c_desc);
}

void info_thread(char *buffer)
{
    char *str = strchr(buffer, ' ');
    str++; str++;
    char *t_uuid = strtok(str, " ");
    char *t_u_uuid = strtok(NULL, " ");
    char *t_name = strtok(NULL, "\""); strtok(NULL, "\"");
    char *t_desc = strtok(NULL, "\""); strtok(NULL, "\"");
    char *t_time = strtok(NULL, "\"");
    time_t currentTime = time(NULL);
    struct tm *timeInfos = localtime(&currentTime); struct tm tm;
    tm.tm_isdst = timeInfos->tm_isdst;
    strptime(t_time, "%a %b %d %H:%M:%S %Y", &tm); time_t t = mktime(&tm);
    client_print_thread(t_uuid, t_u_uuid, t, t_name, t_desc);
}

void info_command_receive(client_t *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    str++;
    if (strstr(str, "ERROR")) {
        int val = str[6] - '0';
        if (val == 1) client_error_unknown_team(client->team_uuid);
        if (val == 2) client_error_unknown_channel(client->channel_uuid);
        if (val == 3) client_error_unknown_thread(client->thread_uuid);
        return;
    }
    if (strstr(buffer, " 1 ")) info_team(buffer);
    if (strstr(buffer, " 2 ")) info_channel(buffer);
    if (strstr(buffer, " 3 ")) info_thread(buffer);
}
