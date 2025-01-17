/*
** EPITECH PROJECT, 2023
** server_commands.c
** File description:
** server_commands
*/

#include "server.h"

int commands(struct client *cli, char *buffer)
{
    if (strstr(buffer, "/login")) {
        login_command(cli, buffer); return 0;
    }
    if (strcmp(buffer, "/logout") == 0) {
        logout_command(cli); return 1;
    }
    if (strcmp(buffer, "/users") == 0) {
        users_command(cli); return 0;
    }
    if (strstr(buffer, "/user")) {
        user_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "/send")) {
        send_command(buffer, cli); return 0;
    }
    if (strstr(buffer, "/messages")) {
        messages_command(buffer, cli); return 0;
    }
    return (other_commands(cli, buffer));
}

int other_commands(struct client *cli, char *buffer)
{
    if (strstr(buffer, "create_team")) {
        create_team_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "create_channel")) {
        create_channel_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "create_thread")) {
        create_thread_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "create_reply")) {
        create_reply_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "/info")) {
        info_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "/list")) {
        list_command(cli, buffer); return 0;
    }
    return (more_commands(cli, buffer));
}

int more_commands(struct client *cli, char *buffer)
{
    if (strstr(buffer, "/subscribed")) {
        subscribed_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "/subscribe")) {
        subscribe_command(cli, buffer); return 0;
    }
    if (strstr(buffer, "/logout_signal")) {
        logout_signal_command(cli); return 0;
    }
    if (strstr(buffer, "/unsubscribe")) {
        unsubscribe_command(cli, buffer); return 0;
    }
    write(cli->sock, UNKNOWN_CMD, strlen(UNKNOWN_CMD));
    return 0;
}

int check_commands_socket(struct client *cli)
{
    int valread; char buffer[MAX_BODY_LENGTH] = {0};
    if ((valread = recv(cli->sock, buffer, 1, 0)) <= 0) {
        catch_client_logout(cli); return 1;
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
        cli->buffer = malloc(sizeof(char) * MAX_BODY_LENGTH);
        memset(cli->buffer, 0, MAX_BODY_LENGTH);
    }
    return 0;
}

// to fix error with memory management
void operations_on_sockets(fd_set *fd, struct client *tmp)
{
    int val = 0;
    LIST_FOREACH(tmp, &head, next) {
        if (FD_ISSET(tmp->sock, fd)) {
            val = check_commands_socket(tmp);
        }
        if (val == 1) {
            val = 0;
        }
    }
}
