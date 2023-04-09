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

typedef struct client {
    int sock;
    char *username;
    char id[37];
    char *buffer;
    int context;
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
    int login;
} client_t;

typedef struct reply {
    char *thread_uuid;
    char *user_uuid;
    time_t timestamp;
    char *body;
} reply_t;

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
void list_threads(client_t *client);
void list_replies(client_t *client);
// RECEIVE COMMANDS:
void receive_commands(struct client *client);
void receive_message(char *buffer);
void handle_received_data(client_t *client);
void receive_users(char *buffer);
// BUFFER HANDLING:
int is_buffer_ended(client_t *client);
//AUTH HANDLING:
void log_unauthorized(void);
//MESSAGES HISTORY:
void send_messages_command(char *buffer, struct client *client);
void receive_messages_history(char *buffer, struct client *client);
void print_history(char *token, char *id, char *msg, struct client *client);
// UTILITIES:
char *clean_text(char *text);
char *get_file_line(int id, char *uuid, char *dir);
int check_if_file_exist(char *uuid, char *dir);
int check_if_title_exist(char *title, char *dir);
