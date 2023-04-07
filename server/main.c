/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include "server.h"

void do_handler(int sig)
{
    unload_users_from_save();
    if (sig >= 0)
        exit(0);
    return;
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
    act.sa_handler = do_handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    create_save_folder();
    create_server(av[1]);
    return 0;
}
