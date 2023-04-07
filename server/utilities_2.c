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
