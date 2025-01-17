/*
** EPITECH PROJECT, 2023
** client.h
** File description:
** client
*/

#pragma once
#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <uuid/uuid.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../libs/myteams/logging_client.h"

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
struct save_reply {
    char *r_body;
    time_t t_time;
};

struct save_thread {
    char *t_name;
    char *t_uuid;
    char *t_desc;
    time_t t_time;
};

struct save_channel {
    char *c_name;
    char *c_uuid;
    char *c_desc;
};

struct save_team {
    char *t_name;
    char *t_uuid;
    char *t_desc;
};

typedef struct client {
    int sock;
    char *username;
    char id[37];
    char *buffer;
    char in_buffer[MAX_BODY_LENGTH];
    int context;
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
    int login;
    struct save_team *s_team;
    struct save_channel *s_channel;
    struct save_thread *s_thread;
    struct save_reply *s_reply;
} client_t;

void create_client(char *ip, char *port);
// COMMANDS:
void send_commands(client_t *client);
void login_command(client_t *client, char *buff);
void logout_command(client_t *client, char *buffer);
void users_command(client_t *client);
void receive_users(char *buffer);
void user_command(client_t *client, char *buffer);
void receive_user(char *buffer);
void help_command(void);
void send_command(char *buffer, struct client *client);
void use_command(client_t *client, char *buffer);
void info_command(client_t *client);
void info_command_receive(client_t *client, char *buffer);
void check_create_commands(client_t *client, char *buffer);
void create_team_command(client_t *client, char *buffer);
void create_channel_command(client_t *client, char *buffer);
void create_thread_command(client_t *client, char *buffer);
void create_reply_command(client_t *client, char *buffer);
void list_command(client_t *client);
void list_threads(client_t *client, char *buffer);
void list_replies(client_t *client, char *buffer);
int check_if_error(char *str, client_t *client);
void subscribe_command(client_t *client, char *buffer);
void subscribed_command(client_t *client, char *buffer);
// RECEIVE COMMANDS:
void receive_commands(struct client *client);
void receive_message(char *buffer);
void handle_received_data(client_t *client);
void receive_users(char *buffer);
void handle_received_more(client_t *client);
void event_channel_created(char *buffer);
void event_thread_created(char *buffer);
void event_reply_created(char *buffer);
void event_team_created(client_t *client);
// BUFFER HANDLING:
int is_buffer_ended(client_t *client);
int is_in_buffer_ended(client_t *client);
//AUTH HANDLING:
void write_log_unauthorized(void);
//MESSAGES HISTORY:
void send_messages_command(char *buffer, struct client *client);
void receive_messages_history(char *buffer, struct client *client);
void print_history(char *token, char *id, char *msg, struct client *client);
// UTILITIES:
char *clean_text(char *text);
char *get_file_line(int id, char *uuid, char *dir);
int check_if_file_exist(char *uuid, char *dir);
int check_if_title_exist(char *title, char *dir);
void list_command_receive(client_t *client, char *buffer);
void send_data_to_socket(int socket, char *data);
//EVENT HANDLING
void get_client_login_event(client_t *client);
void get_client_logout_event(client_t *client);
void free_client(client_t *client);
