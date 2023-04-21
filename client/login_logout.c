/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "client.h"

void check_if_client_exist(FILE *fp, client_t *client, char *user)
{
    char *line = malloc(sizeof(char) * MAX_BODY_LENGTH); int readLen = 1;
    size_t len = 0;char buffer[256] = {0};
    fd_set fds;FD_ZERO(&fds);FD_SET(fileno(fp), &fds);
    select(fileno(fp) + 1, &fds, NULL, NULL, NULL); int foundUser = 0;
    while (read(fileno(fp), buffer, readLen) > 0) {
        select(fileno(fp) + 1, &fds, NULL, NULL, NULL);
        if (buffer[0] == '\n') {
            if (strcmp(line, user) == 0) {
                foundUser = 1; readLen = UUID_STR_LEN - 1;
            }
            free(line); line = NULL; len = 0;
            line = malloc(sizeof(char) * MAX_BODY_LENGTH);
            memset(line, '\0', MAX_BODY_LENGTH); continue;
        }
        if (foundUser == 1) {
            strcpy(client->id, buffer); fclose(fp); free(line);return;
        } strcat(line, buffer); len++;
    }
    free(line); fclose(fp);
    fp = fopen("log.txt", "a"); FD_ZERO(&fds);FD_SET(fileno(fp), &fds);
    select(fileno(fp) + 1, NULL, &fds, NULL, NULL); fprintf(fp, "%s\n", user);
    uuid_t uuid; uuid_generate_random(uuid); uuid_unparse(uuid, client->id);
    fprintf(fp, "%s\n", client->id); fclose(fp);
}

void login_command(client_t *client, char *buff)
{
    char *username = strchr(buff, '"'); int sock = client->sock;
    if (username != NULL && username[1] != '\0')
        username++;
    else
        return;
    if (username[strlen(username) - 1] == '"')
        username[strlen(username) - 1] = '\0';
    else
        return;
    client->username = strcpy(client->username, username);
    FILE *fp = fopen("log.txt", "r"); if (fp == NULL) {
        uuid_t uuid; uuid_generate_random(uuid);
        uuid_unparse(uuid, client->id); fp = fopen("log.txt", "w");
        fprintf(fp, "%s\n", username);
        fprintf(fp, "%s\n", client->id); fclose(fp);
    } else
        check_if_client_exist(fp, client, username);
    send_data_to_socket(sock, buff); send_data_to_socket(sock, "\" ");
    send_data_to_socket(sock, client->id);
    send_data_to_socket(client->sock, "\n");
}

void logout_command(client_t *client, char *buffer)
{
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", 1, 0);
}
