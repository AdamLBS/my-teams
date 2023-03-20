/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/

#include <stdio.h>
#include <string.h>

void help(void) {
    printf("USAGE: ./myteams_cli ip port\n       ip   is ");
    printf("the server ip address on which the server socket listens\n      ");
    printf(" port is the port number on which the server socket listens.\n");
}

int main(int ac, char **av) {
    if (ac != 2)
        return 84;
    if (strcmp(av[1], "-help") == 0)
        help();
    return 0;
}