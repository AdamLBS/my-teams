/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "client.h"

void send_command(char *buffer, struct client *client)
{
    char *new_buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
    new_buffer = strcpy(new_buffer, buffer);
    new_buffer = strcat(new_buffer, " ");
    new_buffer = strcat(new_buffer, client->id);
    send(client->sock, new_buffer, strlen(new_buffer), 0);
    send(client->sock, "\n", 1, 0);
}

void receive_message(void *handle, char *buffer)
{
    printf("OUEEEEEE\n");
    buffer += 9; char *uuid; char *msg;
    char *token = strtok(buffer, " ");
    uuid = token;
    token = strtok(NULL, " ");
    msg = token;
    ((int (*)(char const *, char const *))
    dlsym(handle, "client_event_private_message_received"))(uuid, msg);
}
