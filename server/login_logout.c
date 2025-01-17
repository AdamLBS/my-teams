/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "server.h"

void login_command(struct client *client, char *buffer)
{
    char *str = strchr(buffer, ' ');
    if (str != NULL)
        str++;
    else
        return;
    client->username = strdup(strtok(str, "\""));
    client->id = strdup(strtok(NULL, " "));
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(STDERR_FILENO, &read_fds);
    if (do_user_exists(client->id) == 0) {
        save_user(client->id, client->username);
        select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
        server_event_user_created(client->id, client->username);
    }
    select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
    server_event_user_logged_in(client->id);
    set_user_to_logged_in(client->id);
    send_data_to_socket(client->sock, "LOGIN OK\n");
    send_login_event(client);
    check_pending_messages(client);
    load_team_files(client);
}

void logout_command(struct client *client)
{
    server_event_user_logged_out(client->id);
    send_data_to_socket(client->sock, "LOGOUT OK\n");
    set_user_to_logged_out(client->id);
    send_logout_event(client);
    memset(client->username, 0, strlen(client->username));
}

void catch_client_logout(struct client *client)
{
    if (client->username && strlen(client->username) > 0
    && client->sock != -1) {
        fd_set read_fds; FD_ZERO(&read_fds); FD_SET(STDERR_FILENO, &read_fds);
        select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
        server_event_user_logged_out(client->id);
        set_user_to_logged_out(client->id);
        send_logout_event(client);
        memset(client->username, 0, strlen(client->username));
    }
    client->sock = -1;
}

void load_team_files(struct client *client)
{
    DIR *dir;dir = opendir("./teams/");struct dirent *direc;if (!dir) return;
    for (int i = 0; (direc = readdir(dir)) != NULL; i++) {
        if (strlen(direc->d_name) < 36) continue;
        char *uuid = strdup(direc->d_name), *path; uuid[36] = '\0';
        path =
        malloc(sizeof(char) * ((strlen("./teams/") + strlen(direc->d_name)
        + 1))); strcpy(path, "./teams/"); strcat(path, direc->d_name);
        if (check_user_teams(client, uuid) == 1) {
            load_teams(client, uuid);
        }
    }
    closedir(dir);
}

void logout_signal_command(struct client *client)
{
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(STDERR_FILENO, &read_fds);
    select(STDERR_FILENO + 1, NULL, &read_fds, NULL, NULL);
    server_event_user_logged_out(client->id);
    set_user_to_logged_out(client->id);
    memset(client->username, 0, strlen(client->username));
    client->sock = -1;
}
