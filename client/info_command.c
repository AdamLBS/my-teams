/*
** EPITECH PROJECT, 2023
** info_command.c
** File description:
** info_command
*/

#include "client.h"

void info_command(client_t *client)
{
    if (client->context == 0)
        send(client->sock, "/users\n", 7, 0);
}
