/*
** EPITECH PROJECT, 2023
** client.c
** File description:
** client
*/

#include "client.h"

static void handle_ctrl_c(int sig)
{
    if (sig >= 0) {
    }
}

void catch_ctrl_c(client_t *client)
{
    if (client->login) {
        logout_command(client, "/logout_signal");
        client_event_logged_out(client->id, client->username);
        free_client(client); exit (0);
    }
    exit (0);
}

void set_struct_client(client_t *cl)
{
    cl->username = malloc(sizeof(char) * MAX_NAME_LENGTH);
    memset(cl->username, 0, MAX_NAME_LENGTH);
    cl->context = 0;
    cl->team_uuid = NULL;
    cl->channel_uuid = NULL;
    cl->thread_uuid = NULL;
    cl->login = 0;
    cl->s_team = malloc(sizeof(struct save_team));
    cl->s_channel = malloc(sizeof(struct save_channel));
    cl->s_thread = malloc(sizeof(struct save_thread));
    cl->s_reply = malloc(sizeof(struct save_reply));
}

void receive_commands(struct client *client)
{
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(client->sock, &read_fds);
    struct timeval timeout; timeout.tv_sec = 0; timeout.tv_usec = 150;
    int ready = select(client->sock + 1, &read_fds, NULL, NULL, &timeout);
    if (ready == -1) {
        catch_ctrl_c(client);
    } else if (ready == 0)
        return;
    char tmpBuffer[MAX_BODY_LENGTH];
    memset(tmpBuffer, 0, MAX_BODY_LENGTH);
    int valread = recv(client->sock, tmpBuffer, 1, 0);
    strcat(client->buffer, tmpBuffer);
    if (!is_buffer_ended(client))
        return;
    if (valread > 0) {
        handle_received_data(client);
        memset(client->buffer, 0, MAX_BODY_LENGTH * 2);
    }
}

void create_client(char *ip, char *port)
{
    struct sigaction act; act.sa_handler = handle_ctrl_c;
    sigemptyset(&act.sa_mask);sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0; sigaction(SIGINT, &act, NULL);
    client_t client;
    client.buffer = malloc(sizeof(char) * MAX_BODY_LENGTH * 2);
    memset(client.buffer, 0, MAX_BODY_LENGTH * 2);
    memset(client.in_buffer, 0, MAX_BODY_LENGTH);
    client.sock = socket(AF_INET, SOCK_STREAM, 0);
    set_struct_client(&client);
    struct sockaddr_in myaddr; myaddr.sin_family = AF_INET;
    inet_aton(ip, &myaddr.sin_addr); myaddr.sin_port = htons(atoi(port));
    connect(client.sock, (struct sockaddr *)&myaddr, sizeof(myaddr));
    while (1) {
        receive_commands(&client);
        send_commands(&client);
    }
}
