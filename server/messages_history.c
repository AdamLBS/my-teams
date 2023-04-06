/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Debian]
** File description:
** messages_history
*/

#include "server.h"

void messages_command(char *buffer, struct client *client)
{
    char *id = strchr(buffer, '"');
    if (id != NULL) id++;
    else return;
    if (id[strlen(id) - 1] == '"') id[strlen(id) - 1] = '\0';
    else return;
    char ***msg = get_messages_list(id, client);
    if (!msg) {
        send(client->sock, "msg_history: ", 13, 0);
        send(client->sock, id, strlen(id), 0);
        send(client->sock, " ERROR\n", 7, 0); return;
    }
    for (int i = 0; msg[i]; i++) {
        char *full_msg = get_msg(msg[i]);
        send(client->sock, "msg_history: ", 13, 0); usleep(100);
        send(client->sock, full_msg, strlen(full_msg), 0); usleep(100);
        free(full_msg);
    }
    free_message_history_data(msg);
}

char *get_msg(char **value)
{
    uuid_t uuid;
    char *full_msg = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(full_msg, 0, MAX_BODY_LENGTH);
    int i = 0;
    for (i = 0; value[i] && uuid_parse(value[i], uuid) == -1; i++) {
        strcat(full_msg, value[i]);
        if (value[i + 1] && uuid_parse(value[i + 1], uuid) == -1)
            strcat(full_msg, " ");
    }
    strcat (full_msg, " ");
    for (; value[i]; i++) {
        strcat(full_msg, value[i]);
        strcat (full_msg, " ");
    }
    strcat(full_msg, "\n");
    return full_msg;
}

char ***get_messages_list(char *uuid, struct client *client)
{
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 500);
    char ***messages = malloc(sizeof(char **) * 500);
    memset(file, 0, 500); memset(path, 0, MAX_DESCRIPTION_LENGTH);
    memset(messages, 0, 500);
    strcpy(path, "messages/"); strcat(path, client->id); strcat(path, ".txt");
    FILE *fd = fopen(path, "r");
    if (!fd)
        return NULL;
    char *line = NULL; size_t len = 0; int i = 0;
    while (getline(&line, &len, fd) != -1) {
        if (strstr(line, uuid)) {
            file[i] = line; line = NULL; i++;
        }
    }
    fclose(fd);
    if (i == 0)
        return NULL;
    fill_messages_history(messages, file); free(path);
    return messages;
}

void free_message_history_data(char ***msg)
{
    for (int i = 0; msg[i]; i++) {
        for (int j = 0; msg[i][j]; j++) {
            free(msg[i][j]);
        }
        free(msg[i]);
    }
    free(msg);
}

void fill_messages_history(char ***messages, char **file)
{
    for (int i = 0; file[i]; i++) {
        char *token = strtok(file[i], " ");
        int j = 0;
        messages[i] = malloc(sizeof(char *) * 150);
        memset(messages[i], 0, 150);
        while (token != NULL) {
            messages[i][j] = malloc(sizeof(char) * strlen(token) + 1);
            memset(messages[i][j], 0, strlen(token) + 1);
            messages[i][j] = strcpy(messages[i][j], token);
            token = strtok(NULL, " ");
            j++;
        }
    }
    for (int i = 0; file[i]; i++) {
        free(file[i]);
    }
    free(file);
}
