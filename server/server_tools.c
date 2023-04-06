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
    cl->buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(cl->buffer, 0, MAX_BODY_LENGTH);
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
            if (tmp->sock != -1)
                close(tmp->sock);
            LIST_REMOVE(tmp, next);
            free(tmp->buffer);
            free(tmp->username);
            free(tmp->buffer);
            free(tmp->id);
            free(tmp);
            return;
        }
    }
}

char *clean_text(char *text)
{
    char *new_text = malloc(sizeof(char) * strlen(text));
    int i = 0;
    int j = 0;
    while (text[i] != '\0') {
        if (text[i] != '"') {
            new_text[j] = text[i];
            j++;
        }
        i++;
    }
    new_text[j] = '\0';
    return new_text;
}
