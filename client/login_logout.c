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
        if (strstr(line, username)) {
            getline(&line, &len, fp);
            char *id = strchr(line, ' '); id++;
            id[strlen(id) - 1] = '\0';
            strcpy(client->id, id); fclose(fp);
            return;
        }
    }
    fclose(fp);
    fp = fopen("log.txt", "a");
    fprintf(fp, "name: %s\n", username);
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_unparse(uuid, client->id);
    fprintf(fp, "id: %s\n", client->id);
    fclose(fp);
}

void login_command(void *handle, client_t *client, char *buffer)
{
    char *username = strchr(buffer, ' ');
    if (username != NULL)
        username++;
    else
        return;
    client->username = strdup(username);
    FILE *fp = fopen("log.txt", "r");
    if (fp == NULL) {
        uuid_t uuid; uuid_generate_random(uuid);
        uuid_unparse(uuid, client->id); fp = fopen("log.txt", "w");
        fprintf(fp, "name: %s\n", username);
        fprintf(fp, "id: %s\n", client->id); fclose(fp);
    } else
        check_if_client_exist(fp, client, username);
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, " ", 1, 0);
    send(client->sock, client->id, strlen(client->id), 0);
    send(client->sock, "\n", 1, 0);
}

void logout_command(void *handle, client_t *client, char *buffer)
{
    ((int (*)(char const *, const char *))
    dlsym(handle, "client_event_logged_out"))(client->id, client->username);
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", 1, 0);
}
