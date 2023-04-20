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
    if (client->context >= 1 && client->team_uuid != NULL)
        free(client->team_uuid);
    if (client->context >= 2 && client->channel_uuid != NULL)
        free(client->channel_uuid);
    if (client->context >= 3 && client->thread_uuid != NULL)
        free(client->thread_uuid);
    free(client->s_team); free(client->s_channel); free(client->s_thread);
    free(client->s_reply); free(client->buffer);
    exit(0);
}

void handle_received_more_3(client_t *client)
{
    if (strncmp(client->buffer, "941", 3) == 0) {
        event_reply_created(client->buffer); return;
    } if (strncmp(client->buffer, "101", 3) == 0) {
        client_error_unauthorized(); return;
    } if (strncmp(client->buffer, "901", 3) == 0) {
        client_print_subscribed(client->id, client->s_team->t_uuid); return;
    } if (strncmp(client->buffer, "user_logged_in: ", 16) == 0) {
        get_client_login_event(client); return;
    } if (strncmp(client->buffer, "user_logged_out: ", 17) == 0) {
        get_client_logout_event(client); return;
    } if (strncmp(client->buffer, "102", 3) == 0) {
        client_error_unauthorized(); return;
    } if (strncmp(client->buffer, "902", 3) == 0) {
        client_print_unsubscribed(client->id, client->s_team->t_uuid); return;
    }
}

void handle_received_more_2(client_t *client)
{
    if (strncmp(client->buffer, "930", 3) == 0) {
        client_print_thread_created(client->s_thread->t_uuid,
            client->id, client->s_thread->t_time,
            client->s_thread->t_name, client->s_thread->t_desc); return;
    } if (strncmp(client->buffer, "931", 3) == 0) {
        event_thread_created(client->buffer); return;
    } if (strncmp(client->buffer, "940", 3) == 0) {
        client_print_reply_created(client->thread_uuid,
            client->id, client->s_reply->t_time,
            client->s_reply->r_body); return;
    }
    if (strncmp(client->buffer, "321", 3) == 0) {
        client_error_unknown_channel(client->channel_uuid); return;
    } if (strncmp(client->buffer, "331", 3) == 0) {
        client_error_unknown_thread(client->s_thread->t_uuid);
    }
    handle_received_more_3(client);
}

void handle_received_more(client_t *client)
{
    if (client->buffer[0] == '3' && client->buffer[2] == '2') {
        client_error_already_exist(); return;
    } if (strncmp(client->buffer, "910", 3) == 0) {
        client_print_team_created(client->s_team->t_uuid,
        client->s_team->t_name, client->s_team->t_desc); return;
    } if (strncmp(client->buffer, "911", 3) == 0) {
        event_team_created(client); return;
    } if (strncmp(client->buffer, "920", 3) == 0) {
        client_print_channel_created(client->s_channel->c_uuid,
        client->s_channel->c_name, client->s_channel->c_desc); return;
    } if (strncmp(client->buffer, "921", 3) == 0) {
        event_channel_created(client->buffer); return;
    } if (strncmp(client->buffer, "311", 3) == 0) {
        client_error_unknown_team(client->team_uuid); return;
    } if (strncmp(client->buffer, "313", 3) == 0) {
        client_error_unknown_team(client->s_team->t_uuid); return;
    }
    handle_received_more_2(client);
}

void handle_received_data(client_t *client)
{
    if (strncmp(client->buffer, "receive:", 8) == 0) {
        receive_message(client->buffer); return;
    } if (strncmp(client->buffer, "users:", 6) == 0) {
        receive_users(client->buffer); return;
    } if (strncmp(client->buffer, "user:", 5) == 0) {
        receive_user(client->buffer); return;
    } if (strncmp(client->buffer, "msg_history:", 12) == 0) {
        receive_messages_history(client->buffer, client); return;
    } if (strncmp(client->buffer, "LOGIN OK\n", 9) == 0) {
        fd_set read_fds; FD_ZERO(&read_fds); FD_SET(STDERR_FILENO, &read_fds);
        select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
        client_event_logged_in(client->id, client->username);client->login = 1;
    } if (strncmp(client->buffer, "LOGOUT OK\n", 10) == 0) {
        client_event_logged_out(client->id, client->username);
        free_client(client);
    } if (strncmp(client->buffer, "/info", 5) == 0) {
        info_command_receive(client, client->buffer); return;
    } if (strncmp(client->buffer, "/list", 5) == 0) {
        list_command_receive(client, client->buffer); return;
    } handle_received_more(client);
}
