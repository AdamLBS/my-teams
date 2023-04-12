/*
** EPITECH PROJECT, 2023
** event_channel.c
** File description:
** event_channel
*/

#include "client.h"

void event_channel_created(char *buffer)
{
    char *str = strchr(buffer, ' ');
    str++;
    char *c_name = strtok(str, "\"");
    strtok(NULL, "\"");
    char *c_uuid = strtok(NULL, "\"");
    strtok(NULL, "\"");
    char *c_desc = strtok(NULL, "\"");
    client_event_channel_created(c_uuid, c_name, c_desc);
}

void event_thread_created(char *buffer)
{
    char *str = strchr(buffer, ' '); str++;
    char *t_uuid = strtok(str, "\""); strtok(NULL, "\"");
    char *id = strtok(NULL, "\""); strtok(NULL, "\"");
    char *t_time = strtok(NULL, "\""); strtok(NULL, "\"");
    char *t_name = strtok(NULL, "\""); strtok(NULL, "\"");
    char *t_body = strtok(NULL, "\""); strtok(NULL, "\"");
    time_t currentTime = time(NULL);
    struct tm *timeInfos = localtime(&currentTime); struct tm tm;
    tm.tm_isdst = timeInfos->tm_isdst;
    strptime(t_time, "%a %b %d %H:%M:%S %Y", &tm); time_t t = mktime(&tm);
    client_event_thread_created(t_uuid, id, t, t_name, t_body);
}

void event_reply_created(char *buffer)
{
    char *str = strchr(buffer, ' '); str++;
    char *t_uuid = strtok(str, "\""); strtok(NULL, "\"");
    char *id = strtok(NULL, "\""); strtok(NULL, "\"");
    char *t_time = strtok(NULL, "\""); strtok(NULL, "\"");
    char *t_body = strtok(NULL, "\""); strtok(NULL, "\"");
    time_t currentTime = time(NULL);
    struct tm *timeInfos = localtime(&currentTime); struct tm tm;
    tm.tm_isdst = timeInfos->tm_isdst;
    strptime(t_time, "%a %b %d %H:%M:%S %Y", &tm); time_t t = mktime(&tm);
    client_print_reply_created(t_uuid, id, t, t_body);
}
