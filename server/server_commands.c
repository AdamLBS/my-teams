/*
** EPITECH PROJECT, 2023
** server_commands.c
** File description:
** server_commands
*/

#include "server.h"

int commands(struct client *cli, char *buffer, void *handle)
{
    if (strstr(buffer, "/login")) {
        login_command(handle, cli, buffer);
        return 0;
    }
    if (strcmp(buffer, "/logout") == 0) {
        logout_command(handle, cli);
        return 1;
    }
    write(cli->sock, "500 Syntax error, ", 18);
    write(cli->sock, "command unrecognized.\n", 22);
    return 0;
}

int check_commands_socket(struct client *cli, void *handle)
{
    int valread; char buffer[MAX_BODY_LENGTH] = {0};
    if ((valread = read(cli->sock, buffer, MAX_BODY_LENGTH)) == 0) {
        remove_client(cli->sock); return 1;
    } else {
        if (cli->buffer[0] != '\0')
            strcat(cli->buffer, buffer);
        else
            strcpy(cli->buffer, buffer);
    }
    if (cli->buffer[strlen(cli->buffer) - 1] == '\n') {
        cli->buffer[strlen((cli->buffer)) - 1] = '\0';
        if (commands(cli, cli->buffer, handle) == 1)
            return 1;
        free(cli->buffer);
        cli->buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
        memset(cli->buffer, 0, MAX_BODY_LENGTH);
    }
    return 0;
}

// to fix error with memory management
void operations_on_sockets(fd_set *fd, void *handle)
{
    struct client *tmp;
    int val = 0;
    LIST_FOREACH(tmp, &head, next) {
        if (FD_ISSET(tmp->sock, fd))
            val = check_commands_socket(tmp, handle);
        if (val == 1) {
            remove_client(tmp->sock);
            val = 0;
        }
    }
}
