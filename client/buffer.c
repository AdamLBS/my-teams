/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Debian]
** File description:
** buffer
*/

#include "client.h"

int is_buffer_ended(client_t *client)
{
    int len = strlen(client->buffer);
    if (len < 2)
        return 0;
    if (client->buffer[len - 1] == '\0')
        return 0;
    if (client->buffer[len - 1] != '\n')
        return 0;
    return 1;
}

int is_in_buffer_ended(client_t *client)
{
    int len = strlen(client->in_buffer);
    if (len < 2) {
        return 0;
    }
    if (client->in_buffer[len - 1] == '\0') {
        return 0;
    }
    if (client->in_buffer[len - 1] != '\n')
        return 0;
    return 1;
}
