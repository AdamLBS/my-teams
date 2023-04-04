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
    int size = strlen("users/") + strlen(user_uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "users/");
    strcat(path, user_uuid);
    strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(user_uuid, 1, strlen(user_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(user_name, 1, strlen(user_name), fd);
    fwrite("\n", 1, 1, fd);
    fwrite("0", 1, 1, fd);
    fclose (fd);
    free(path);
}

int do_user_exists(char *user_uuid)
{
    int size = strlen("users/") + strlen(user_uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "users/");
    strcat(path, user_uuid);
    strcat(path, ".txt");
    FILE *fd = fopen(path, "r");
    if (fd) {
        fclose(fd);
        free(path);
        return 1;
    }
    free(path);
    return 0;
}

void save_server(void)
{
    struct client *tmp;
    LIST_FOREACH(tmp, &head, next) {
        set_user_to_logged_out(tmp->id);
    }
}
