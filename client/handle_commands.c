/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** handle_commands
*/

#include "client.h"

void free_client(client_t *client)
{
    free(client->username);
    close(client->sock);
    free(client->in_buffer);
    if (client->context >= 1 && client->team_uuid != NULL)
        free(client->team_uuid);
    if (client->context >= 2 && client->channel_uuid != NULL)
        free(client->channel_uuid);
    if (client->context >= 3 && client->thread_uuid != NULL)
        free(client->thread_uuid);
    free(client->s_team); free(client->s_channel);
    exit(0);
}

void handle_received_more_2(client_t *client)
{
    if (strstr(client->buffer, "931"))
        event_thread_created(client->buffer);
    if (strstr(client->buffer, "941"))
        event_reply_created(client->buffer);
    if (strstr(client->buffer, "101"))
        client_error_unauthorized();
    if (strstr(client->buffer, "901"))
        client_print_subscribed(client->id, client->team_uuid);
}

void handle_received_more(client_t *client)
{
    if (client->buffer[0] == '3' && client->buffer[2] == '2')
        client_error_already_exist();
    if (strstr(client->buffer, "911"))
        client_event_team_created(client->s_team->t_uuid
        , client->s_team->t_name, client->s_team->t_desc);
    if (strstr(client->buffer, "921"))
        event_channel_created(client->buffer);
    if (strstr(client->buffer, "311"))
        client_error_unknown_team(client->team_uuid);
    if (strstr(client->buffer, "321"))
        client_error_unknown_channel(client->channel_uuid);
    if (strstr(client->buffer, "331"))
        client_error_unknown_thread(client->s_thread->t_uuid);
    handle_received_more_2(client);
}

void handle_received_data(client_t *client)
{
    if (strstr(client->buffer, "receive:"))
        receive_message(client->buffer);
    if (strstr(client->buffer, "users:"))
        receive_users(client->buffer);
    if (strstr(client->buffer, "user:"))
        receive_user(client->buffer);
    if (strstr(client->buffer, "msg_history:"))
        receive_messages_history(client->buffer, client);
    if (strstr(client->buffer, "LOGIN OK\n")) {
        client_event_logged_in(client->id, client->username);client->login = 1;
    }
    if (strstr(client->buffer, "LOGOUT OK\n")) {
        client_event_logged_out(client->id, client->username);
        free_client(client);
    }
    if (strstr(client->buffer, "/info"))
        info_command_receive(client, client->buffer);
    if (strstr(client->buffer, "/list"))
        list_command_receive(client, client->buffer);
    handle_received_more(client);
}
