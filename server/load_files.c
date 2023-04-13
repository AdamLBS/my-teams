/*
** EPITECH PROJECT, 2023
** load_files.c
** File description:
** load_files
*/

#include "server.h"

void load_teams(struct client *cli, char *to_find)
{
    cli->teams[cli->nb_teams + 1] = malloc(sizeof(struct team));
    cli->teams[cli->nb_teams + 1]->uuid = strdup(to_find);
    cli->teams[cli->nb_teams + 1]->name =
    strdup(get_file_line_n(1, to_find, "./teams/"));
    cli->teams[cli->nb_teams + 1]->desc =
    strdup(get_file_line_n(2, to_find, "./teams/"));
    cli->teams[cli->nb_teams + 1]->nb_channels =
    atoi(get_file_line_n(4, to_find, "./teams/"));
    cli->teams[cli->nb_teams + 1]->channels =
    malloc(sizeof(struct channels *) * 100);
    cli->teams[cli->nb_teams + 1]->nb_channels = 0;
    cli->nb_teams++;
    load_channels(cli, cli->nb_teams);
}

void load_channels(struct client *cli, int nb)
{
    DIR *dir;dir = opendir("./channels/");struct dirent *direc;if (!dir) return;
    for (int i = 0, j = 0; (direc = readdir(dir)) != NULL; i++) {
        if (strlen(direc->d_name) < 36) continue;
        char *c_uuid = strdup(direc->d_name), *path; c_uuid[36] = '\0'; path =
        malloc(sizeof(char) * ((strlen("./channels/") + strlen(direc->d_name)
        + 1))); strcpy(path, "./channels/"); strcat(path, direc->d_name);
        FILE *fd = fopen(path, "r"); if (strcmp(cli->teams[nb]->uuid
        , get_file_line_n(3, c_uuid, "./channels/")) != 0) {
            fclose(fd); free(c_uuid); continue; }
        cli->teams[nb]->channels[j] = malloc(sizeof(struct channel)); cli->
        teams[nb]->channels[j]->nb_threads = 0;cli->teams[nb]->nb_channels++;
        cli->teams[nb]->channels[j]->uuid = strdup(c_uuid); cli->teams[nb]->
        channels[j]->name = strdup(get_file_line_n(1, c_uuid, "./channels/"));
        cli->teams[nb]->channels[j]->desc = strdup(get_file_line_n(2, c_uuid
        , "./channels/"));cli->teams[nb]->channels[j]->t_uuid = strdup(
        get_file_line_n(3, c_uuid, "./channels/")); cli->teams[nb]->channels[j]
        ->nb_threads = atoi(get_file_line_n(4, c_uuid, "./channels/"));cli->
        teams[nb]->channels[j]->threads = malloc(sizeof(struct thread *) * 100);
        load_threads(cli, nb, j); free(c_uuid); fclose(fd); j++;
    } closedir(dir);
}

void load_threads(struct client *cli, int nb, int na)
{
    DIR *dir;dir = opendir("./threads/");struct dirent *direc;if (!dir) return;
    for (int i = 0, j = 0; (direc = readdir(dir)) != NULL; i++) {
        if (strlen(direc->d_name) < 36) continue;
        char *t_uuid = strdup(direc->d_name); t_uuid[36] = '\0';
        char *path = malloc(sizeof(char) * ((strlen("./threads/") +
        strlen(direc->d_name) + 1))); strcpy(path, "./threads/"); strcat(path
        , direc->d_name); FILE *fd = fopen(path, "r");
        if (strcmp(cli->teams[nb]->channels[na]->uuid, get_file_line_n(6, t_uuid
        , "./threads/")) != 0) {
            fclose(fd); free(t_uuid); continue;
        }
        struct thread *thr = get_thread_struct(cli->teams[nb], na, j);
        cli->teams[nb]->channels[na]->nb_threads++;
        update_thread_struct(thr, t_uuid);
        load_replies(cli, nb, na, j); free(t_uuid); fclose(fd); j++;
    } closedir(dir);
}

void load_replies(struct client *cli, int nb, int na, int nz)
{
    DIR *dir;dir = opendir("./replies/");struct dirent *direc;if (!dir) return;
    for (int i = 0, j = 0; (direc = readdir(dir)) != NULL; i++) {
        if (strlen(direc->d_name) < 36) continue;
        char *r_uuid = strdup(direc->d_name); r_uuid[36] = '\0';
        char *path = malloc(sizeof(char) * ((strlen("./replies/") +
        strlen(direc->d_name) + 1))); strcpy(path, "./replies/"); strcat(path
        , direc->d_name); FILE *fd = fopen(path, "r");
        if (strcmp(cli->teams[nb]->channels[na]->threads[nz]->uuid
        , get_file_line_n(3, r_uuid , "./replies/")) != 0) {
            fclose(fd); free(r_uuid); continue;
        } struct reply *reply = get_reply_struct(cli->teams[nb], na, nz, j);
        reply->tm_uuid = strdup(get_file_line_n(1, r_uuid, "./replies/"));
        reply->c_uuid = strdup(get_file_line_n(2, r_uuid, "./replies/"));
        reply->t_uuid = strdup(get_file_line_n(3, r_uuid, "./replies/"));
        reply->o_uuid = strdup(get_file_line_n(4, r_uuid, "./replies/"));
        reply->time = strdup(get_file_line_n(5, r_uuid, "./replies/"));
        reply->msg = strdup(get_file_line_n(6, r_uuid, "./replies/"));
        free(r_uuid); fclose(fd); j++;
    } closedir(dir);
}
