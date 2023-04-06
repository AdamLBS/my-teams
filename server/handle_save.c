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
    mkdir("messages", 0755);
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

void save_server(char ***users)
{
    for (int i = 0; users[i]; i++) {
        set_user_to_logged_out(users[i][0]);
    }
}

void unload_users_from_save(void)
{
    DIR *d; struct dirent *dir; char *path = NULL;
    char ***userList = malloc(sizeof(char **) * 100);
    memset(userList, 0, 100);
    int index = 0; d = opendir("users/");
    if (!d)
        return;
    while ((dir = readdir(d)) != NULL) {
        path = dir->d_name;
        if (strlen(path) > 4 && !strcmp(path + strlen(path) - 4, ".txt")) {
            int size = strlen("users/") + strlen(dir->d_name) + 1;
            char *fullpath = malloc(sizeof(char ) * size);
            memset(fullpath, '\0', size);
            strcpy(fullpath, "users/");
            strcat(fullpath, dir->d_name);
            char **val = read_user_from_save(fullpath); free(fullpath);
            userList[index] = val;
            index++;
        }
    }
    save_server(userList); free_userlist(userList); closedir(d);
}
