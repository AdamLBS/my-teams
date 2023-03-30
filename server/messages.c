/*
** EPITECH PROJECT, 2023
** messages.c
** File description:
** messages
*/

#include "server.h"

void send_command(void *handle, struct client *client, char *buffer)
{
    buffer += 6;
    char *r_uuid; char *s_uuid; char *msg;
    char *token;
    printf("buffer: %s\n", buffer);
    token = strtok(buffer, " "); int i = 0;
    if (token != NULL) {
        r_uuid = token;
        token = strtok(NULL, " ");
        msg = token;
        token = strtok(NULL, " ");
        s_uuid = token;
    }
    printf("r_uuid: %s, s_uuid: %s, message: %s\n", r_uuid, s_uuid, msg);
    ((int (*)(char const *, char const *, char const *))
    dlsym(handle, "server_event_private_message_sended"))(s_uuid, r_uuid, msg);
}