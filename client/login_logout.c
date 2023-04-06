/*
** EPITECH PROJECT, 2023
** login_logout.c
** File description:
** login_logout
*/

#include "client.h"

void check_if_client_exist(FILE *fp, client_t *client, char *username)
{
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, fp) != -1) {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, username) == 0) {
            getline(&line, &len, fp);
            line[strlen(line) - 1] = '\0';
            strcpy(client->id, line); fclose(fp);
            return;
        }
    }
    fclose(fp);
    fp = fopen("log.txt", "a");
    fprintf(fp, "%s\n", username);
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_unparse(uuid, client->id);
    fprintf(fp, "%s\n", client->id);
    fclose(fp);
}

void login_command(client_t *client, char *buff)
{
    char *username = strchr(buff, '"');
    if (username != NULL && username[1] != '\0')
        username++;
    else
        return;
    if (username[strlen(username) - 1] == '"')
        username[strlen(username) - 1] = '\0';
    else
        return;
    client->username = strdup(username); FILE *fp = fopen("log.txt", "r");
    if (fp == NULL) {
        uuid_t uuid; uuid_generate_random(uuid);
        uuid_unparse(uuid, client->id); fp = fopen("log.txt", "w");
        fprintf(fp, "%s\n", username);
        fprintf(fp, "%s\n", client->id); fclose(fp);
    } else
        check_if_client_exist(fp, client, username);
    send(client->sock, buff, strlen(buff), 0); send(client->sock, " ", 1, 0);
    send(client->sock, client->id, strlen(client->id), 0);
    send(client->sock, "\n", 1, 0);
}

void logout_command(client_t *client, char *buffer)
{
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", 1, 0);
}
