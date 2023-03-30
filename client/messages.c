/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "client.h"

void send_command(void *handle, char *buffer, struct client *client)
{
    dprintf(client->sock, "%s", buffer);
}