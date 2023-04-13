/*
** EPITECH PROJECT, 2023
** server.h
** File description:
** server
*/

#pragma once
#define _XOPEN_SOURCE
#define _GNU_SOURCE
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
#include <time.h>
#include "../libs/myteams/logging_server.h"

#define MAX_CLIENTS 100
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define MAX_CLIENT_TEAMS 100
#define MAX_TEAM_CHANNELS 100
#define UNKNOWN_CMD "500 Syntax error, command unrecognized.\n"

typedef struct reply {
    char *msg;
    char *uuid;
    char *time;
    char *t_uuid;
    char *tm_uuid;
    char *o_uuid;
    char *c_uuid;
} reply_t;

typedef struct replies {
    char *thread_uuid;
    char *user_uuid;
    char *timestamp;
    char *body;
    time_t time;
} replies_t;

struct thread {
    char *name;
    char *uuid;
    char *body;
    char *c_uuid;
    char *o_uuid;
    char *time;
    char *t_uuid;
    struct reply **replies;
};

struct channel {
    char *name;
    char *uuid;
    char *desc;
    char *t_uuid;
    char *t_name;
    int nb_threads;
    struct thread **threads;
};

struct team {
    char *name;
    char *uuid;
    char *desc;
    int nb_channels;
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
    int nb_teams;
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
void create_channel_command(struct client *client, char *buffer);
void save_message_receiver(char *msg, char *send, char *rcv, bool received);
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
char *get_file_line(int id, char *uuid, char *dir);
void set_file_line(int id, char *uuid, char *target, char *dir);
char *itoa(int num);
void free_userlist(char ***userList);
void create_team_file(char *t_uuid, char *t_name, char *t_desc);
void create_c_file(char *c_uuid, char *c_name, char *t_uuid, char *c_desc);
int find_t(char *t_uuid, struct client *client);
int find_c(char *c_uuid, struct client *client, char *team_uuid);
void create_thread_file(struct thread *thread);
void create_thread_command(struct client *client, char *buffer);
void check_pending_messages(struct client *client);
char ***get_all_messages(struct client *client);
char *get_waiting_msg(char **value);
char **get_file_data(char *path);
void write_file_data(char *path, char **data);
void clear_message_queue(struct client *client);
int is_message_waiting(char **msg);
int find_th(char *c_uuid, struct client *client, char *team_uuid,
char *thread_uuid);
void create_reply_command(struct client *client, char *buffer);
void create_reply_file(struct reply *reply);
void info_command(struct client *client, char *buffer);
char *get_file_line_n(int id, char *uuid, char *dir);
void list_command(struct client *client, char *buffer);
void list_threads(struct client *client, char *team_uuid, char *channel_uuid);
void list_replies(struct client *client, char *team_uuid, char *channel_uuid
, char *thread_uuid);
int find_last_line(char *path);
void write_new_member(char *u_uuid, char *t_uuid);
int check_if_file_exist(char *uuid, char *dir);
int check_if_title_exist(char *title, char *dir);
int check_team_error(struct client *client, char *t_uuid, char *team_name);
int check_permissions(struct client *client, char *uuid);
int check_channel_error(struct client *client, char *c_name, char *t_uuid
, char *c_uuid);
void subscribe_command(struct client *cli, char *buffer);
int more_commands(struct client *cli, char *buffer);
void load_teams(struct client *cli, char *to_find);
void load_channels(struct client *cli, int nb);
void put_r(struct reply *reply, char *uuid, char *tm_uuid, char *t_uuid);
void put_s(struct thread *thread, char *time, char *t_uuid, char *o_uuid);
void load_threads(struct client *cli, int nb, int na);
void load_replies(struct client *cli, int nb, int na, int nz);
void subscribed_command(struct client *cli, char *buffer);
struct reply *get_reply_struct(struct team *team, int na, int nz, int i);
struct thread *get_thread_struct(struct team *team, int na, int i);
void update_thread_struct(struct thread *thr, char *t_uuid);
void send_login_event(struct client *cli);
void send_logout_event(struct client *cli);
void logout_signal_command(struct client *client);
void erase_line(char *to_find, char *dir, char *uuid);
void unsubscribe_command(struct client *cli, char *buffer);
void remove_team_from_struct(char *uuid, struct client *cli);
