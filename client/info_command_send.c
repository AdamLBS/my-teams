/*
** EPITECH PROJECT, 2023
** info_command_send.c
** File description:
** info_command_send
*/

#include "client.h"

char *itoa(int num)
{
    int len = snprintf(NULL, 0, "%d", num);
    char* str = malloc(sizeof(char) * (len + 1));
    snprintf(str, len + 1, "%d", num);
    return str;
}

void send_info_command(client_t *client)
{
    send(client->sock, "/info ", 6, 0);
    send(client->sock, itoa(client->context), 1, 0);
    send(client->sock, " ", 1, 0);
    if (client->context >= 1)
        send(client->sock, client->team_uuid, strlen(client->team_uuid), 0);
    if (client->context >= 2) {
        send(client->sock, " ", 1, 0);
        send(client->sock, client->channel_uuid
        , strlen(client->channel_uuid), 0);
    }
    if (client->context >= 3) {
        send(client->sock, " ", 1, 0);
        send(client->sock, client->thread_uuid
        , strlen(client->thread_uuid), 0);
    }
    send(client->sock, "\n", 1, 0);
}

void info_command(client_t *client)
{
    if (client->context == 0)
        send(client->sock, "/users\n", 7, 0);
    if (client->context == 1) {
        send_info_command(client);
    }
    if (client->context == 2) {
        send_info_command(client);
    }
    if (client->context == 3) {
        send_info_command(client);
    }
}
