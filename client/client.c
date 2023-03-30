/*
** EPITECH PROJECT, 2023
** client.c
** File description:
** client
*/

#include "client.h"

void *get_lib(void)
{
    void *handle = dlopen("./libs/myteams/libmyteams.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    return handle;
}

void set_struct_client(client_t *cl)
{
    cl->username = malloc(sizeof(char) * MAX_NAME_LENGTH);
}

void receive_commands(void *handle, struct client *client)
{
    char buffer[MAX_BODY_LENGTH];
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(client->sock, &read_fds);
    struct timeval timeout; timeout.tv_sec = 0; timeout.tv_usec = 1;
    int ready = select(client->sock + 1, &read_fds, NULL, NULL, &timeout);
    if (ready == -1) {
        perror("select");
        return;
    } else if (ready == 0)
        return;
    int valread = recv(client->sock, buffer, sizeof(buffer), 0);
    if (valread < 0) {
        perror("recv"); return;
    } else if (valread == 0) {
        return;
    } else {
        if (strstr(buffer, "receive:"))
            receive_message(handle, buffer);
    }
}

void create_client(char *ip, char *port)
{
    void *handle = get_lib();
    client_t client;
    client.sock = socket(AF_INET, SOCK_STREAM, 0);
    set_struct_client(&client);
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    inet_aton(ip, &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    connect(client.sock, (struct sockaddr *)&myaddr, sizeof(myaddr));
    while (1) {
        receive_commands(handle, &client);
        send_commands(handle, &client);
    }
    dlclose(handle);
}
