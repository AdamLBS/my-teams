/*
** EPITECH PROJECT, 2023
** server_commands.c
** File description:
** server_commands
*/

#include "server.h"

int commands(struct client *cli, char *buffer)
{
    if (strcmp(buffer, "NOOP") == 0) {
        write(cli->sock, "200 Command okay.\n", 18);
        return 0;
    }
    write(cli->sock, "500 Syntax error, ", 18);
    write(cli->sock, "command unrecognized.\n", 22);
    return 0;
}

int check_commands_socket(struct client *cli)
{
    int valread; char buffer[1025] = {0};
    if ((valread = read(cli->sock, buffer, 1024)) == 0) {
        remove_client(cli->sock); return 1;
    } else {
        if (cli->buffer[0] != '\0')
            strcat(cli->buffer, buffer);
        else
            strcpy(cli->buffer, buffer);
    }
    if (cli->buffer[strlen(cli->buffer) - 1] == '\n') {
        cli->buffer[strlen((cli->buffer)) - 1] = '\0';
        if (commands(cli, cli->buffer) == 1)
            return 1;
        free(cli->buffer);
        cli->buffer = malloc(sizeof(char) * 1025);
        memset(cli->buffer, 0, 1024);
    }
    return 0;
}

void operations_on_sockets(fd_set *fd)
{
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (FD_ISSET(tmp->sock, fd))
            check_commands_socket(tmp);
    }
}
