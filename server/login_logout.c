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
    if (do_user_exists(client->id) == 0) {
        save_user(client->id, client->username);
        server_event_user_created(client->id, client->username);
    }
    server_event_user_logged_in(client->id);
    set_user_to_logged_in(client->id);
    send(client->sock, "LOGIN OK\n", 9, 0);
    send_login_event(client);
    check_pending_messages(client);
    load_team_files(client);
}

void logout_command(struct client *client)
{
    server_event_user_logged_out(client->id);
    send(client->sock, "LOGOUT OK\n", 10, 0);
    set_user_to_logged_out(client->id);
    send_logout_event(client);
    memset(client->username, 0, strlen(client->username));
}

void catch_client_logout(struct client *client)
{
    if (strlen(client->username) > 0 && client->sock != -1) {
        server_event_user_logged_out(client->id);
        set_user_to_logged_out(client->id);
        send_logout_event(client);
    }
    client->sock = -1;
}


int check_user_teams(struct client *client, char *t_uuid)
{
    char *path = malloc(sizeof(char) * 50);
    memset(path, '\0', 50); size_t len = 0;
    strcpy(path, "./teams/"); strcat(path, t_uuid); strcat(path, ".txt");
    FILE *fd = fopen(path, "r");
    char *line = NULL;
    while (getline(&line, &len, fd) != -1) {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, client->id) == 0) {
            return 1;
        }
    }
    return 0;
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

void logout_signal_command(struct client *client)
{
    server_event_user_logged_out(client->id);
    set_user_to_logged_out(client->id);
    memset(client->username, 0, strlen(client->username));
    client->sock = -1;
}
