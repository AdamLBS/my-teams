/*
** EPITECH PROJECT, 2023
** create_file.c
** File description:
** create_file
*/

#include "server.h"

void create_team_file(char *t_uuid, char *t_name, char *t_desc)
{
    int size = strlen("teams/") + strlen(t_uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "teams/");
    strcat(path, t_uuid);
    strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(t_uuid, 1, strlen(t_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(t_name, 1, strlen(t_name), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(t_desc, 1, strlen(t_desc), fd);
    fwrite("\n", 1, 1, fd);
    fwrite("0", 1, 1, fd);
    fwrite("\n", 1, 1, fd);
    fwrite("0", 1, 1, fd);
    fclose (fd);
    free(path);
}

void create_c_file(char *c_uuid, char *c_name, char *t_uuid, char *c_desc)
{
    int size = strlen("channels/") + strlen(c_uuid) + 6;
    char *path = malloc(sizeof(char) * size);
    memset(path, '\0', size);
    strcpy(path, "channels/");
    strcat(path, c_uuid);
    strcat(path, ".txt");
    FILE *fd = fopen(path, "w");
    fwrite(c_uuid, 1, strlen(c_uuid), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(c_name, 1, strlen(c_name), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(c_desc, 1, strlen(c_desc), fd);
    fwrite("\n", 1, 1, fd);
    fwrite(t_uuid, 1, strlen(t_uuid), fd);
    fclose (fd);
    free(path);
}