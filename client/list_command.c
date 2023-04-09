/*
** EPITECH PROJECT, 2023
** list_command.c
** File description:
** list_command
*/

#include "client.h"

void list_teams(char *buffer)
{
    char *str = strchr(buffer, ' ');
    if (str != NULL)
        str++;
    else
        return;
    char *token = strtok(str, "\"");
    while (token != NULL) {
        char *uuid = token; strtok(NULL, "\"");
        token = strtok(NULL, "\"");
        char *name = token; strtok(NULL, "\"");
        token = strtok(NULL, "\"");
        char *desc = token; strtok(NULL, "\"");
        token = strtok(NULL, "\"");
        client_print_teams(uuid, name, desc);
    }
}

void list_channels(client_t *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    if (str != NULL) str++;
    else
        return;
    if (strstr(str, "ERROR")) {
        int val = str[6] - '0';
        if (val == 1) client_error_unknown_team(client->team_uuid);
        if (val == 2) client_error_unknown_channel(client->channel_uuid);
        if (val == 3) client_error_unknown_thread(client->thread_uuid);
        return;
    }
    char *token = strtok(str, "\"");
    while (token != NULL) {
        char *uuid = token; strtok(NULL, "\"");
        token = strtok(NULL, "\"");
        char *name = token; strtok(NULL, "\"");
        token = strtok(NULL, "\"");
        char *desc = token; strtok(NULL, "\""); token = strtok(NULL, "\"");
        client_team_print_channels(uuid, name, desc);
    }
}

void list_command(client_t *client)
{
    if (client->context == 0)
        send(client->sock, "/list 0\n", 8, 0);
    if (client->context == 1) {
        send(client->sock, "/list 1 ", 8, 0);
        send(client->sock, client->team_uuid, strlen(client->team_uuid), 0);
        send(client->sock, "\n", 1, 0);
    } if (client->context == 2) {
        send(client->sock, "/list 2 ", 8, 0);
        send(client->sock, client->team_uuid, strlen(client->team_uuid), 0);
        send(client->sock, " ", 1, 0);send(client->sock, client->channel_uuid
        , strlen(client->channel_uuid), 0); send(client->sock, "\n", 1, 0);
    } if (client->context == 3) {
        send(client->sock, "/list 3 ", 8, 0);
        send(client->sock, client->team_uuid, strlen(client->team_uuid), 0);
        send(client->sock, " ", 1, 0);
        send(client->sock, client->channel_uuid, strlen(client->channel_uuid)
        , 0); send(client->sock, " ", 1, 0);
        send(client->sock, client->thread_uuid, strlen(client->thread_uuid), 0);
        send(client->sock, "\n", 1, 0);
    }
}

void list_command_receive(client_t *client, char *buffer)
{
    if (client->context == 0)
        list_teams(buffer);
    if (client->context == 1)
        list_channels(client, buffer);
    if (client->context == 2)
        list_threads(client, buffer);
    if (client->context == 3)
        list_replies(client, buffer);
}
