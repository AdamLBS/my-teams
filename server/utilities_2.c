/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** utilities_2
*/

#include "server.h"

void write_file_data(char *path, char **data)
{
    FILE *fd = fopen(path, "w");
    for (int i = 0; data[i]; i++) {
        fputs(data[i], fd);
        fputs("\n", fd);
    }
    fclose(fd);
}

char *get_file_line_n(int id, char *uuid, char *dir)
{
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, dir);
    strcat(path, uuid);
    strcat(path, ".txt");
    fd = fopen(path, "r");
    if (!fd)
        return NULL;
    while (getline(&line, &len, fd) != -1) {
        if (i == id) {
            fclose(fd); free(path); free(file);
            line[strlen(line) - 1] = '\0';
            return line;
        }
        i++;
    }
    fclose(fd); free(path); free(file);
    return NULL;
}

int check_permissions(struct client *client, char *uuid)
{
    int i = 0;
    while (i <= client->nb_teams) {
        if (strcmp(client->teams[i]->uuid, uuid) == 0)
            return 0;
        i++;
    }
    return 1;
}

int check_user_teams(struct client *client, char *t_uuid)
{
    char *path = malloc(sizeof(char) * 50);
    memset(path, '\0', 50); size_t len = 0;
    strcpy(path, "./teams/"); strcat(path, t_uuid); strcat(path, ".txt");
    FILE *fd = fopen(path, "r");
    fd_set read_fds;FD_ZERO(&read_fds);FD_SET(fileno(fd), &read_fds);
    select(fileno(fd) + 1, &read_fds, NULL, NULL, NULL);
    char *line = NULL;
    while (getline(&line, &len, fd) != -1) {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, client->id) == 0) {
            return 1;
        }
        select(fileno(fd) + 1, &read_fds, NULL, NULL, NULL);
    }
    return 0;
}

void send_data_to_socket(int socket, char *data)
{
    fd_set read_fds; FD_ZERO(&read_fds); FD_SET(socket, &read_fds);
    select(socket + 1, NULL, &read_fds, NULL, NULL);
    send(socket, data, strlen(data), 0);
}
