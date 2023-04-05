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
}

void receive_commands(struct client *client)
{
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(client->sock, &read_fds);
    struct timeval timeout; timeout.tv_sec = 0; timeout.tv_usec = 200;
    int ready = select(client->sock + 1, &read_fds, NULL, NULL, &timeout);
    if (ready == -1) {
        perror("select"); return;
    } else if (ready == 0)
        return;
    char tmpBuffer[MAX_BODY_LENGTH];
    memset(tmpBuffer, 0, MAX_BODY_LENGTH);
    int valread = recv(client->sock, tmpBuffer, sizeof(tmpBuffer), 0);
    strcat(client->buffer, tmpBuffer);
    if (!is_buffer_ended(client))
        return;
    if (valread > 0) {
        handle_received_data(client);
        memset(client->buffer, 0, MAX_BODY_LENGTH);
    }
}

void create_client(char *ip, char *port)
{
    client_t client;
    client.buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(client.buffer, 0, MAX_BODY_LENGTH);
    client.sock = socket(AF_INET, SOCK_STREAM, 0);
    set_struct_client(&client);
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    inet_aton(ip, &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    connect(client.sock, (struct sockaddr *)&myaddr, sizeof(myaddr));
    while (1) {
        receive_commands(&client);
        send_commands(&client);
    }
}
