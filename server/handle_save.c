/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL : Ubuntu]
** File description:
** handle_save
*/

#include "server.h"

void create_save_folder(void)
{
    mkdir("users", 0755);
}

void save_user(char *user_uuid, char *user_name)
{
    char *path = malloc(sizeof(char) * strlen("users/") + strlen(user_uuid) + 1);
    memset(path, '\0', strlen("users/") + strlen(user_uuid) + 1);
    strcpy(path, "users/");
    strcat(path, user_uuid);
    FILE *fd = fopen(path, "w");
    fwrite(user_uuid, 1, strlen(user_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(user_name, 1, strlen(user_name), fd);
    fclose (fd);
    free(path);
}

int do_user_exists(char *user_uuid)
{
    char *path = malloc(sizeof(char) * strlen("users/") + strlen(user_uuid) + 1);
    strcpy(path, "users/");
    strcat(path, user_uuid);
    FILE *fd = fopen(path, "r");
    if (fd) {
        fclose(fd);
        return 1;
    }
    return 0;
}

void save_server(struct client *cli)
{
    (cli);
    return;
}
