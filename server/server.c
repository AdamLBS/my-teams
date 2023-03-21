/*
** EPITECH PROJECT, 2023
** server.c
** File description:
** server
*/

#include "server.h"

struct list_head head;

void free_all_clients(void)
{
    while (!LIST_EMPTY(&head)) {
        struct client *elem = LIST_FIRST(&head);
        LIST_REMOVE(elem, next);
        free(elem->buffer);
        free(elem->username);
        free(elem);
    }
}

void create_server(char *port)
{
    LIST_INIT(&head);
    int max_sd;
    fd_set readfds; int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr; int addrlen = sizeof(myaddr);
    myaddr.sin_family = AF_INET; inet_aton("0.0.0.0", &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    bind(master_socket, (struct sockaddr *)&myaddr, sizeof(myaddr));
    listen(master_socket, MAX_CLIENTS);
    while (1) {
        add_and_set_sockets(&readfds, &max_sd, master_socket);
        int ret_val = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (ret_val <= 0)
            perror("select()");
        if (FD_ISSET(master_socket, &readfds))
            accept_socket(master_socket, myaddr, addrlen);
        operations_on_sockets(&readfds);
    }
    close(master_socket);
    free_all_clients();
}
