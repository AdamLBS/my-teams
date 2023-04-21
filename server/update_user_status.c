/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Debian]
** File description:
** update_user_status
*/

#include "server.h"

void set_user_to_logged_in(char *uid)
{
    FILE *fd; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, "users/");strcat(path, uid); strcat(path, ".txt");
    file = get_file_data(path, 1);
    file[2] = strdup("1\n"); fd = fopen(path, "w");
    fd_set fds;FD_ZERO(&fds);FD_SET(fileno(fd), &fds);
    FD_SET(fileno(fd), &fds); select(fileno(fd) + 1, NULL, &fds, NULL, NULL);
    for (i = 0; file[i]; i++) {
        fputs(file[i], fd); free(file[i]);
        select(fileno(fd) + 1, NULL, &fds, NULL, NULL);
    } fclose(fd); free(path); free(file);
}

void set_user_to_logged_out(char *uid)
{
    FILE *fd; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100);
    memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, "users/"); strcat(path, uid); strcat(path, ".txt");
    fd_set fds;FD_ZERO(&fds);
    file = get_file_data(path, 1);
    file[2] = strdup("0\n"); fd = fopen(path, "w");FD_ZERO(&fds);
    FD_SET(fileno(fd), &fds); select(fileno(fd) + 1, NULL, &fds, NULL, NULL);
    for (i = 0; file[i]; i++) {
        fputs(file[i], fd); free(file[i]);
        select(fileno(fd) + 1, NULL, &fds, NULL, NULL);
    } fclose(fd); free(path); free(file);
}
