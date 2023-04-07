/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Debian]
** File description:
** save_messages
*/

#include "server.h"

void save_message_receiver(char *msg, char *send, char *rcv, bool received)
{
    time_t timestamp = time(NULL); char *time = ctime(&timestamp);
    time[strlen(time) - 1] = '\0';
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 1000);
    memset(file, 0, 100); memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, "messages/"); strcat(path, rcv); strcat(path, ".txt");
    fd = fopen(path, "r"); if (fd) {
        while (getline(&line, &len, fd) != -1) {
            file[i] = line; line = NULL; i++;
        } fclose(fd);
    } int size = strlen(msg) + strlen(send) + strlen(time) + 10;
    char *msg_val = malloc(sizeof(char) * size);
    memset(msg_val, 0, size); strcat(msg_val, msg); strcat(msg_val, " ");
    strcat(msg_val, send); strcat(msg_val, " "); strcat(msg_val, time);
    strcat (msg_val, " 0"); file[i] = msg_val; fd = fopen(path, "w");
    strcat(msg_val, itoa(received)); strcat(msg_val, "\n");
    for (i = 0; file[i]; i++) {
        fputs(file[i], fd); free(file[i]);
    }fclose(fd); free(path); free(file);
}

void save_message_sender(char *msg, char *send, char *rcv)
{
    time_t timestamp = time(NULL); char *time = ctime(&timestamp);
    time[strlen(time) - 1] = '\0';
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 1000);
    memset(file, 0, 100); memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, "messages/"); strcat(path, send); strcat(path, ".txt");
    fd = fopen(path, "r");
    if (fd) {
        while (getline(&line, &len, fd) != -1) {
            file[i] = line; line = NULL; i++;
        } fclose(fd);
    }
    int size = strlen(msg) + strlen(send) + strlen(time) + 10;
    char *msg_val = malloc(sizeof(char) * size); memset(msg_val, 0, size);
    strcat(msg_val, msg); strcat(msg_val, " "); strcat(msg_val, rcv);
    strcat(msg_val, " "); strcat(msg_val, time); strcat (msg_val, " 11");
    file[i] = msg_val; fd = fopen(path, "w");
    strcat(msg_val, "\n"); for (i = 0; file[i]; i++) fputs(file[i], fd);
    fclose(fd); free(path); free(file); free(msg_val);
}
