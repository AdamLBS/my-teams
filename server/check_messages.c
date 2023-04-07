/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** check_messages
*/

#include "server.h"

void check_pending_messages(struct client *client)
{
    char ***msg = get_all_messages(client);
    if (!msg) {
        return;
    }
    for (int i = 0; msg[i]; i++) {
        if (msg[i] && is_message_waiting(msg[i])) {
                char *full_msg = get_waiting_msg(msg[i]);
                send(client->sock, "receive: ", 9, 0);
                send(client->sock, full_msg, strlen(full_msg), 0);
                free(full_msg);
        }
    }
    clear_message_queue(client);
}

char ***get_all_messages(struct client *client)
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
            file[i] = line; line = NULL; i++;
    }
    fclose(fd);
    if (i == 0) {
        free(path); return NULL;
    }
    fill_messages_history(messages, file); free(path); return messages;
}

char *get_waiting_msg(char **value)
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
    char *uuid_val = malloc(sizeof(char) * 37);
    memset(uuid_val, 0, 37);
    strcpy(uuid_val, value[i]);
    int size = strlen(full_msg) + strlen(uuid_val) + 3;
    char *msg = malloc(sizeof(char) * size);
    memset(msg, 0, size);
    strcpy(msg, uuid_val); strcat(msg, " "); strcat(msg, full_msg);
    strcat(msg, "\n"); return msg;
}

void clear_message_queue(struct client *client)
{
    char *path = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(path, 0, MAX_BODY_LENGTH);
    strcpy(path, "messages/"); strcat(path, client->id); strcat(path, ".txt");
    char **file = get_file_data(path);
    if (!file)
        return;
    for (int i = 0; file[i]; i++) {
        if (file[i][strlen(file[i]) - 1] == '0') {
            file[i][strlen(file[i]) - 1] = '1';
        }
    }
    write_file_data(path, file);
    for (int i = 0; file[i]; i++) {
        free(file[i]);
    }
    free(file); free(path);
}

int is_message_waiting(char **msg)
{
    int i = 0;
    for (i = 0; msg[i]; i++);
    if (msg[i - 1][1] == '0')
        return 1;
    return 0;
}
