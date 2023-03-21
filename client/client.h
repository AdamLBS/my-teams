/*
** EPITECH PROJECT, 2023
** client.h
** File description:
** client
*/

#ifndef CLIENt
    #define CLIENT

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

void create_client(char *ip, char *port);

#endif /* !CLIENT */