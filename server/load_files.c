/*
** EPITECH PROJECT, 2023
** load_files.c
** File description:
** load_files
*/

#include "server.h"

void load_teams(struct client *cli, char *to_find)
{
    cli->nb_teams++;
    cli->teams[cli->nb_teams + 1] = malloc(sizeof(struct team));
    cli->teams[cli->nb_teams + 1]->uuid = strdup(to_find);
    cli->teams[cli->nb_teams + 1]->name =
    strdup(get_file_line_n(1, to_find, "./teams/"));
    cli->teams[cli->nb_teams + 1]->desc =
    strdup(get_file_line_n(2, to_find, "./teams/"));
    cli->teams[cli->nb_teams + 1]->nb_channels =
    atoi(get_file_line_n(4, to_find, "./teams/"));
    cli->teams[cli->nb_teams + 1]->channels = malloc(sizeof(struct channels *));
    load_channels(cli, cli->nb_teams + 1);
}

void load_channels(struct client *cli, int nb)
{
    DIR *dir;dir = opendir("./channels/");struct dirent *direc;if (!dir) return;
    for (int i = 0; (direc = readdir(dir)) != NULL; i++) {
        if (strlen(direc->d_name) < 36) continue;
        char *c_uuid = strdup(direc->d_name); c_uuid[36] = '\0';
        char *path = malloc(sizeof(char) * ((strlen("./channels/") +
        strlen(direc->d_name) + 1))); strcpy(path, "./channels/"); strcat(path
        , direc->d_name); FILE *fd = fopen(path, "r");
        if (strcmp(cli->teams[nb]->uuid, get_file_line_n(3, c_uuid
        , "./channels/")) != 0) {
            fclose(fd); free(c_uuid); continue;
        } cli->teams[nb]->channels[i] = malloc(sizeof(struct channel));
        cli->teams[nb]->nb_channels++;
        cli->teams[nb]->channels[i]->uuid = strdup(c_uuid);
        cli->teams[nb]->channels[i]->name = strdup(get_file_line_n(1, c_uuid
        , "./channels/")); cli->teams[nb]->channels[i]->desc = strdup(
        get_file_line_n(2, c_uuid, "./channels/"));
        cli->teams[nb]->channels[i]->t_uuid = strdup(get_file_line_n(3, c_uuid
        , "./channels/")); cli->teams[nb]->channels[i]->nb_threads = atoi(
        get_file_line_n(4, c_uuid, "./channels/"));
        cli->teams[nb]->channels[i]->threads = malloc(sizeof(struct thread *));
        load_threads(cli, nb, i); free(c_uuid); fclose(fd);
    } closedir(dir);
}

void load_threads(struct client *cli, int nb, int na)
{
    DIR *dir;dir = opendir("./threads/");struct dirent *direc;if (!dir) return;
    for (int i = 0; (direc = readdir(dir)) != NULL; i++) {
        if (strlen(direc->d_name) < 36) continue;
        char *t_uuid = strdup(direc->d_name); t_uuid[36] = '\0';
        char *path = malloc(sizeof(char) * ((strlen("./threads/") +
        strlen(direc->d_name) + 1))); strcpy(path, "./threads/"); strcat(path
        , direc->d_name); FILE *fd = fopen(path, "r");
        if (strcmp(cli->teams[nb]->channels[na]->uuid, get_file_line_n(6, t_uuid
        , "./threads/")) != 0) {
            fclose(fd); free(t_uuid); continue;
        }
        struct thread *thr = get_thread_struct(cli->teams[nb], na, i);
        cli->teams[nb]->channels[na]->nb_threads++;
        update_thread_struct(thr, t_uuid);
        load_replies(cli, nb, na, i); free(t_uuid); fclose(fd);
    } closedir(dir);
}

void load_replies(struct client *cli, int nb, int na, int nz)
{
    DIR *dir;dir = opendir("./replies/");struct dirent *direc;if (!dir) return;
    for (int i = 0; (direc = readdir(dir)) != NULL; i++) {
        if (strlen(direc->d_name) < 36) continue;
        char *r_uuid = strdup(direc->d_name); r_uuid[36] = '\0';
        char *path = malloc(sizeof(char) * ((strlen("./replies/") +
        strlen(direc->d_name) + 1))); strcpy(path, "./replies/"); strcat(path
        , direc->d_name); FILE *fd = fopen(path, "r");
        if (strcmp(cli->teams[nb]->channels[na]->threads[nz]->uuid, get_file_line_n(3, r_uuid
        , "./replies/")) != 0) {
            fclose(fd); free(r_uuid); continue;
        } struct reply *reply = get_reply_struct(cli->teams[nb], na, nz, i);
        reply = strdup(get_file_line_n(1, r_uuid, "./replies/"));
        reply = strdup(get_file_line_n(2, r_uuid, "./replies/"));
        reply = strdup(get_file_line_n(3, r_uuid, "./replies/"));
        reply = strdup(get_file_line_n(4, r_uuid, "./replies/"));
        reply = strdup(get_file_line_n(5, r_uuid, "./replies/"));
        reply = strdup(get_file_line_n(6, r_uuid, "./replies/"));
        free(r_uuid); fclose(fd);
    } closedir(dir);
}
