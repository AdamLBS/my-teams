/*
** EPITECH PROJECT, 2023
** server.h
** File description:
** server
*/

#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/queue.h>
#include <dlfcn.h>

#define MAX_CLIENTS 100
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

struct client {
    int sock;
    const char *username;
    int passwd;
    char id[37];
    char *buffer;
    struct sockaddr_in addr;
    LIST_ENTRY(client) next;
};

extern LIST_HEAD(list_head, client) head;

void create_server(char *port);
void accept_socket(int m_sock, struct sockaddr_in addr, int rl);
void operations_on_sockets(fd_set *fd, void *handle);
void add_and_set_sockets(fd_set *fd, int *m_sd, int m_sock);
void remove_client(int socket);
void login_command(void *handle, struct client *client, char *buffer);
void logout_command(void *handle, struct client *client);
