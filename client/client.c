/*
** EPITECH PROJECT, 2023
** client.c
** File description:
** client
*/

#include "client.h"

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
    FD_SET(STDIN_FILENO, &read_fds);
    int ready = select(client->sock + 1, &read_fds, NULL, NULL, NULL);
    if (ready <= 0)
        return;
    char tmpBuffer[MAX_BODY_LENGTH];
    memset(tmpBuffer, 0, MAX_BODY_LENGTH);
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        send_commands(client); return;
    }
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
    client_t client;
    client.buffer = malloc(sizeof(char) * MAX_BODY_LENGTH * 2);
    memset(client.buffer, 0, MAX_BODY_LENGTH * 2);
    memset(client.in_buffer, 0, MAX_BODY_LENGTH);
    client.sock = socket(AF_INET, SOCK_STREAM, 0);
    set_struct_client(&client);
    struct sockaddr_in myaddr; myaddr.sin_family = AF_INET;
    inet_aton(ip, &myaddr.sin_addr); myaddr.sin_port = htons(atoi(port));
    int val = connect(client.sock, (struct sockaddr *)&myaddr, sizeof(myaddr));
    if (val != 0) {
        printf("Connection failed\n"); exit(84);
    }
    while (1) {
        receive_commands(&client);
    }
}
