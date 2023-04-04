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
#include <errno.h>
#include <stdbool.h>

#define MAX_CLIENTS 100
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define UNKNOWN_CMD "500 Syntax error, command unrecognized.\n"

struct client {
    int sock;
    char *username;
    int passwd;
    char *id;
    char *buffer;
    struct sockaddr_in addr;
    LIST_ENTRY(client) next;
};

extern LIST_HEAD(list_head, client) head;

void create_server(char *port);
void accept_socket(int m_sock, struct sockaddr_in addr, int rl);
void operations_on_sockets(fd_set *fd, void *handle, struct client *tmp);
void add_and_set_sockets(fd_set *fd, int *m_sd, int m_sock);
void remove_client(int socket);
void login_command(void *handle, struct client *client, char *buffer);
void logout_command(void *handle, struct client *client);
void users_command(struct client *client);
void user_command(struct client *client, char *buffer);
void send_command(void *handle, char *buffer);
void create_save_folder(void);
void save_user(char *user_uuid, char *user_name);
int do_user_exists(char *user_uuid);
void save_server(void);
char **read_user_from_save(char *path);
void load_users_from_save(void *handle);
void send_user_loaded(char ***userList, void *handle);
void get_users_from_save(struct client *client);
void set_user_to_logged_in(char *uid);
void set_user_to_logged_out(char *uid);
void send_users(char ***userList, struct client *client);
void send_user(char **user, struct client *client);
