/*
** EPITECH PROJECT, 2023
** create_server.c
** File description:
** create_server
*/

#include "server.h"

void add_new_socket_to_array(int cfd, struct sockaddr_in addr)
{
    struct client *cl = malloc(sizeof(struct client));
    cl->addr = addr;
    cl->sock = cfd;
    cl->username = NULL;
    cl->passwd = 0;
    cl->buffer = malloc(sizeof(char) * MAX_NAME_LENGTH);
    memset(cl->buffer, 0, MAX_NAME_LENGTH);
    read(cl->sock, cl->id, 37);
    LIST_INSERT_HEAD(&head, cl, next);
}

void accept_socket(int m_sock, struct sockaddr_in addr, int rl)
{
    int cfd = accept(m_sock, (struct sockaddr*)&addr, (socklen_t*)&rl);
    if (cfd < 0)
        exit(EXIT_FAILURE);
    add_new_socket_to_array(cfd, addr);
}

void add_and_set_sockets(fd_set *fd, int *m_sd, int m_sock)
{
    int sd;
    FD_ZERO(fd);
    FD_SET(m_sock, fd);
    *m_sd = m_sock;
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        sd = tmp->sock;
        if (sd > 0)
            FD_SET(sd, fd);
        if (sd > *m_sd)
            *m_sd = sd;
    }
}

void remove_client(int socket)
{
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (tmp->sock == socket) {
            close(tmp->sock);
            LIST_REMOVE(tmp, next);
            free(tmp->buffer);
            free(tmp);
            return;
        }
    }
}