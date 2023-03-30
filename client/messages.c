/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "client.h"

void send_command(void *handle, char *buffer, struct client *client)
{
    char *new_buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
    new_buffer = strcpy(new_buffer, buffer);
    new_buffer = strcat(new_buffer, " ");
    new_buffer = strcat(new_buffer, client->id);
    send(client->sock, new_buffer, strlen(new_buffer), 0);
    send(client->sock, "\n", 1, 0);
}