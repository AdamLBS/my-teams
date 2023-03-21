/*
** EPITECH PROJECT, 2023
** client.c
** File description:
** client
*/

#include "client.h"

void create_client(char *ip, char *port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    inet_aton(ip, &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    connect(sock, (struct sockaddr *)&myaddr, sizeof(myaddr));
    while (1) {
        char *buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
        read(0, buffer, MAX_BODY_LENGTH);
        write(sock, buffer, strlen(buffer));
        free(buffer);
        buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
        read(sock, buffer, MAX_BODY_LENGTH);
        printf("%s", buffer);
        free(buffer);
    }
}
