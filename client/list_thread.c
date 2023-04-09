/*
** EPITECH PROJECT, 2023
** list_thread.c
** File description:
** list_thread
*/

#include "client.h"

void list_threads(client_t *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    if (str != NULL) str++;
    else
        return;
    if (check_if_error(str, client)) return;
    char *token = strtok(str, "\"");
    while (token != NULL) {
        char *t_uuid = token; strtok(NULL, "\"");
        token = strtok(NULL, "\"");char *t_u_uuid = token; strtok(NULL, "\"");
        token = strtok(NULL, "\""); char *t_name = token; strtok(NULL, "\"");
        token = strtok(NULL, "\""); char *t_desc = token; strtok(NULL, "\"");
        token = strtok(NULL, "\""); char *t_time = token; strtok(NULL, "\"");
        token = strtok(NULL, "\""); time_t currentTime = time(NULL);
        struct tm *timeInfos = localtime(&currentTime); struct tm tm;
        tm.tm_isdst = timeInfos->tm_isdst;
        strptime(t_time, "%a %b %d %H:%M:%S %Y", &tm); time_t t = mktime(&tm);
        client_channel_print_threads(t_uuid, t_u_uuid, t, t_name, t_desc);
    }
}
