/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include "server.h"

void help(void)
{
    printf("USAGE: ./myteams_server port\n\t");
    printf("port is the port number on which the server socket listens.\n");
    exit(0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (strcmp(av[1], "-help") == 0)
        help();
    create_save_folder();
    create_server(av[1]);
    return 0;
}
