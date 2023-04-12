/*
** EPITECH PROJECT, 2023
** subscribed.c
** File description:
** subscribed
*/

#include "client.h"

void subscribed_command(client_t *client, char *buffer)
{
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", strlen("\n"), 0);
    if (strcmp(buffer, "/subscribed") == 0)
        return;
    char *str = strchr(buffer, ' '); str++;
    client->s_team->t_uuid = clean_text(str);
}
