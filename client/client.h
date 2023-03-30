/*
** EPITECH PROJECT, 2023
** client.h
** File description:
** client
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
#include <dlfcn.h>
#include <uuid/uuid.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

typedef struct client {
    int sock;
    char *username;
    char id[37];
} client_t;

void create_client(char *ip, char *port);
// COMMANDS:
void send_commands(void *handle, client_t *client);
void login_command(void *handle, client_t *client, char *buffer);
void logout_command(void *handle, client_t *client, char *buffer);
void users_command(void *handle, client_t *client);
void user_command(void *handle, client_t *client, char *buffer);
void help_command(void);
void send_command(char *buffer, struct client *client);
// RECEIVE COMMANDS:
void receive_commands(void *handle, client_t *client);
void receive_message(void *handle, char *buffer);