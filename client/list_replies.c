/*
** EPITECH PROJECT, 2023
** list_replies.c
** File description:
** list_replies
*/

#include "client.h"

int check_if_error(char *str, client_t *client)
{
    if (strstr(str, "ERROR")) {
        int val = str[6] - '0';
        if (val == 1) client_error_unknown_team(client->team_uuid);
        if (val == 2) client_error_unknown_channel(client->channel_uuid);
        if (val == 3) client_error_unknown_thread(client->thread_uuid);
        return 1;
    }
    return 0;
}

void list_replies(client_t *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    if (str != NULL) str++;
    else
        return;
    if (check_if_error(str, client)) return;
    char *token = strtok(str, "\"");
    while (token != NULL) {
        char *uuid = token; strtok(NULL, "\""); token = strtok(NULL, "\"");
        char *t_uuid = token; strtok(NULL, "\""); token = strtok(NULL, "\"");
        char *body = token; strtok(NULL, "\""); token = strtok(NULL, "\"");
        char *timestamp = token; strtok(NULL, "\""); token = strtok(NULL, "\"");
        time_t currentTime = time(NULL);
        struct tm *timeInfos = localtime(&currentTime); struct tm tm;
        tm.tm_isdst = timeInfos->tm_isdst;
        strptime(timestamp, "%a %b %d %H:%M:%S %Y", &tm);
        time_t t = mktime(&tm);
        client_thread_print_replies(uuid, t_uuid, t, body);
    }
}
