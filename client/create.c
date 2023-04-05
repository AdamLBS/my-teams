/*
** EPITECH PROJECT, 2023
** create.c
** File description:
** create
*/

#include "client.h"

void check_create_commands(client_t *client, char *buffer)
{
    if (client->context == 0)
        create_team_command(client, buffer);
    // else if (client->context == 1)
    //     create_channel_command(client, buffer);
    // else if (client->context == 2)
    //     create_thread_command(client, buffer);
    // else if (client->context == 3)
    //     create_reply_command(client, buffer);
}

void create_team_command(client_t *client, char *buffer)
{
    char team_uuid[37]; uuid_t uuid; uuid_generate_random(uuid);
    uuid_unparse(uuid, team_uuid); buffer += 8;
    buffer[strlen(buffer)] = '\0'; char *t_name; char *t_desc;
    char *token = strtok(buffer, " ");
    t_name = token; token = strtok(NULL, ""); t_desc = token;
    client_event_team_created(team_uuid, t_name, t_desc);
    send(client->sock, "create_team", 11, 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, team_uuid, 36, 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, t_name, strlen(t_name), 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, t_desc, strlen(t_desc), 0);
    send(client->sock, "\n", 1, 0);
}

// void create_channel_command(client_t *client, char *buffer)
// {

// }

// void create_thread_command(client_t *client, char *buffer)
// {

// }

// void create_reply_command(client_t *client, char *buffer)
// {

// }