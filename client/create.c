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
    if (client->context == 1)
        create_channel_command(client, buffer);
    else if (client->context == 2)
        create_thread_command(client, buffer);
}

void create_team_command(client_t *client, char *buffer)
{
    char team_uuid[37]; uuid_t uuid; uuid_generate_random(uuid);
    uuid_unparse(uuid, team_uuid); buffer += 8;
    buffer[strlen(buffer)] = '\0'; char *t_name; char *t_desc;
    char *token = strtok(buffer, "\""); t_name = token;
    strtok(NULL, "\""); token = strtok(NULL, ""); t_desc = token;
    t_name = clean_text(t_name); t_desc = clean_text(t_desc);
    client_event_team_created(team_uuid, t_name, t_desc);
    send(client->sock, "create_team", 11, 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, team_uuid, 36, 0);
    send(client->sock, " \"", 2, 0);
    send(client->sock, t_name, strlen(t_name), 0);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, t_desc, strlen(t_desc), 0);
    send(client->sock, "\"\n", 2, 0);
}

void create_channel_command(client_t *client, char *buffer)
{
    if (check_if_file_exist(client->team_uuid, "./teams/") == 0) {
        client_error_unknown_team(client->team_uuid); return;
    }
    char channel_uuid[37]; uuid_t uuid; uuid_generate_random(uuid);
    uuid_unparse(uuid, channel_uuid); buffer += 8;
    buffer[strlen(buffer)] = '\0'; char *c_name; char *c_desc;
    char *token = strtok(buffer, "\""); c_name = token;
    strtok(NULL, "\""); token = strtok(NULL, ""); c_desc = token;
    c_name = clean_text(c_name); c_desc = clean_text(c_desc);
    client_event_channel_created(channel_uuid, c_name, c_desc);
    send(client->sock, "create_channel", 14, 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, client->team_uuid, 36, 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, channel_uuid, 36, 0);
    send(client->sock, " \"", 1, 0);
    send(client->sock, c_name, strlen(c_name), 0);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, c_desc, strlen(c_desc), 0);
    send(client->sock, "\"\n", 2, 0);
}

void create_thread_command(client_t *client, char *buffer)
{
    if (check_if_file_exist(client->channel_uuid, "./channels/") == 0) {
        client_error_unknown_team(client->channel_uuid); return;
    }
    time_t curTime = time( NULL );
    char t_uuid[37]; uuid_t uuid; uuid_generate_random(uuid);
    uuid_unparse(uuid, t_uuid); buffer += 8; buffer[strlen(buffer)] = '\0';
    char *t_name; char *t_body; char *token = strtok(buffer, "\"");
    t_name = token; strtok(NULL, "\""); token = strtok(NULL, "");
    t_body = token; t_name = clean_text(t_name); t_body = clean_text(t_body);
    client_event_thread_created(t_uuid, client->id, curTime, t_name, t_body);
    send(client->sock, "create_thread", 13, 0); send(client->sock, " ", 1, 0);
    send(client->sock, client->team_uuid, 36, 0);send(client->sock, " ", 1, 0);
    send(client->sock, client->channel_uuid, 36, 0);
    send(client->sock, " ", 1, 0); send(client->sock, client->id, 36, 0);
    send(client->sock, " ", 1, 0); send(client->sock, t_uuid, 36, 0);
    send(client->sock, " \"", 1, 0);
    send(client->sock, t_name, strlen(t_name), 0);
    send(client->sock, "\" \"", 3, 0);
    send(client->sock, t_body, strlen(t_body), 0);
    send(client->sock, "\"\n", 2, 0);
}
