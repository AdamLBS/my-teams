/*
** EPITECH PROJECT, 2023
** create_channel.c
** File description:
** create_channel
*/

#include "server.h"

int check_channel_error(struct client *client, char *c_name, char *t_uuid
, char *c_uuid)
{
    if (check_if_file_exist(t_uuid, "./teams/") == 0) {
        send(client->sock, "311\n", 4, 0); return 1;
    }
    if (check_if_file_exist(c_uuid, "./channels/") == 1) {
        send(client->sock, "321\n", 4, 0); return 1;
    }
    if (check_if_title_exist(c_name, "./channels/") == 1) {
        send(client->sock, "322\n", 4, 0); return 1;
    }
    if (check_permissions(client, t_uuid) == 1) {
        send(client->sock, "101\n", 4, 0); return 1;
    }
    return 0;
}

void send_info_channel(struct client *client, int i, int j)
{
    send(client->sock, "920\n", 4, 0);
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        if (check_permissions(tmp, client->teams[i]->uuid) != 1) {
            tmp->teams[i] = client->teams[i];
            send(tmp->sock, "921 \"", 5, 0);
            send(tmp->sock, client->teams[i]->channels[j]->name
            , strlen(client->teams[i]->channels[j]->name), 0);
            send(tmp->sock, "\" \"", 3, 0);
            send(tmp->sock, client->teams[i]->channels[j]->uuid, 36, 0);
            send(tmp->sock, "\" \"", 3, 0);
            send(tmp->sock, client->teams[i]->channels[j]->desc
            , strlen(client->teams[i]->channels[j]->desc), 0);
            send(tmp->sock, "\"\n", 2, 0);
        }
    }
}

void create_channel_command(struct client *client, char *buffer)
{
    char *c_name; char *c_uuid; char *team_uuid; char *c_desc;
    buffer += 15; buffer[strlen(buffer)] = '\0'; char *token =
    strtok(buffer, " "); team_uuid = token; token = strtok(NULL, " ");
    c_uuid = token; token = strtok(NULL, "\""); c_name = token;
    strtok(NULL, "\""); token = strtok(NULL, "\""); c_desc = token;
    if (check_channel_error(client, c_name, team_uuid, c_uuid) == 1) return;
    server_event_channel_created(team_uuid, c_uuid, c_name);
    int i = find_t(team_uuid, client);
    int n_channel = atoi(get_file_line(4, team_uuid, "teams/"));
    client->teams[i]->nb_channels = n_channel; set_file_line(4, team_uuid,
    itoa(n_channel + 1), "teams/");
    client->teams[i]->channels[n_channel] = malloc(sizeof(struct channel));
    client->teams[i]->channels[n_channel]->name = strdup(c_name);
    client->teams[i]->channels[n_channel]->uuid = strdup(c_uuid);
    client->teams[i]->channels[n_channel]->desc = strdup(c_desc);
    client->teams[i]->channels[n_channel]->t_uuid = strdup(team_uuid);
    client->teams[i]->channels[n_channel]->nb_threads = 0;
    client->teams[i]->channels[n_channel]->threads =
    malloc(sizeof(struct thread *) * 100); create_c_file(c_uuid, c_name
    , team_uuid, c_desc); send_info_channel(client, i, n_channel);
}

void create_c_file(char *c_uuid, char *c_name, char *t_uuid, char *c_desc)
{
    int size = strlen("channels/") + strlen(c_uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "channels/");
    strcat(path, c_uuid); strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(c_uuid, 1, strlen(c_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(c_name, 1, strlen(c_name), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(c_desc, 1, strlen(c_desc), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(t_uuid, 1, strlen(t_uuid), fd);
    fwrite("\n0\n", 1, 3, fd);
    fclose (fd);
    free(path);
}
