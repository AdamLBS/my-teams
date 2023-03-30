/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include "server.h"

static bool keepRunning = true;

void intHandler(int) {
    keepRunning = false;
}

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
    struct sigaction act;
    act.sa_handler = intHandler;  
    sigaction(SIGINT, &act, NULL );  
    create_save_folder();
    while (keepRunning) {
        create_server(av[1]);
    }
    return 0;
}
