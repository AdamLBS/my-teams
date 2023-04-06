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
#include <uuid/uuid.h>
#include "../libs/myteams/logging_server.h"

#define MAX_CLIENTS 100
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define MAX_CLIENT_TEAMS 100
#define MAX_TEAM_CHANNELS 100
#define UNKNOWN_CMD "500 Syntax error, command unrecognized.\n"

struct channel {
    char *name;
    char *uuid;
    char *desc;
    char *t_uuid;
    char *t_name;
};

struct team {
    char *name;
    char *uuid;
    char *desc;
    struct channel **channels;
};

struct client {
    int sock;
    char *username;
    int passwd;
    char *id;
    char *buffer;
    struct sockaddr_in addr;
    struct team **teams;
    LIST_ENTRY(client) next;
};

extern LIST_HEAD(list_head, client) head;

void create_server(char *port);
void accept_socket(int m_sock, struct sockaddr_in addr, int rl);
void operations_on_sockets(fd_set *fd, struct client *tmp);
void add_and_set_sockets(fd_set *fd, int *m_sd, int m_sock);
void remove_client(int socket);
void login_command(struct client *client, char *buffer);
void logout_command(struct client *client);
void users_command(struct client *client);
void user_command(struct client *client, char *buffer);
void send_command(char *buffer, struct client *client);
void create_save_folder(void);
void save_user(char *user_uuid, char *user_name);
int do_user_exists(char *user_uuid);
void save_server(char ***users);
char **read_user_from_save(char *path);
void load_users_from_save(void);
void send_user_loaded(char ***userList);
void get_users_from_save(struct client *client);
void set_user_to_logged_in(char *uid);
void set_user_to_logged_out(char *uid);
void send_users(char ***userList, struct client *client);
void send_user(char **user, struct client *client);
int commands(struct client *cli, char *buffer);
void create_team_command(struct client *client, char *buffer);
int other_commands(struct client *cli, char *buffer);
void unload_users_from_save(void);
void create_channel_command(char *buffer);
void save_message_receiver(char *msg, char *send, char *rcv);
void save_message_sender(char *msg, char *send, char *rcv);
void messages_command(char *buffer, struct client *client);
char ***get_messages_list(char *uuid, struct client *client);
char *get_msg(char **value);
void catch_client_logout(struct client *client);
void free_message_history_data(char ***msg);
void fill_messages_history(char ***messages, char **file);
void send_error(struct client *client, char *id);
char *remove_quotes_send_cmd(char *str);
char *clean_text(char *text);
char *get_user_line(int id, char *uuid);
void set_user_line(int id, char *uuid, char *target);
char *itoa(int num);
void free_userlist(char ***userList);
