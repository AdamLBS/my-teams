/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** utilities_2
*/

#include "server.h"

void write_file_data(char *path, char **data)
{
    FILE *fd = fopen(path, "w");
    for (int i = 0; data[i]; i++) {
        fputs(data[i], fd);
        fputs("\n", fd);
    }
    fclose(fd);
}

char *get_file_line_n(int id, char *uuid, char *dir)
{
    FILE *fd; char *line = NULL; size_t len = 0; int i = 0;
    char *path = malloc(sizeof(char) * MAX_DESCRIPTION_LENGTH);
    char **file = malloc(sizeof(char *) * 100); memset(file, 0, 100);
    memset(path, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(path, dir);
    strcat(path, uuid);
    strcat(path, ".txt");
    fd = fopen(path, "r");
    if (!fd)
        return NULL;
    while (getline(&line, &len, fd) != -1) {
        if (i == id) {
            fclose(fd); free(path); free(file);
            line[strlen(line) - 1] = '\0';
            return line;
        }
        i++;
    }
    fclose(fd); free(path); free(file);
    return NULL;
}

int check_permissions(struct client *client, char *uuid)
{
    int i = 0;
    printf("nb teams: %i\n", client->nb_teams);
    while (i <= client->nb_teams) {
        if (strcmp(client->teams[i]->uuid, uuid) == 0)
            return 0;
        i++;
    }
    return 1;
}
