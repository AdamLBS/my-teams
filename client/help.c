/*
** EPITECH PROJECT, 2023
** help.c
** File description:
** help
*/

#include "client.h"

void help_command(void)
{
    printf("HELP\n");
    printf("  /login [username]\n");
    printf("  /logout\n");
    printf("  /users\n");
    printf("  /user [user_uuid]\n");
    printf("  /send [user_uuid] [message]\n");
    printf("  /messages [user_uuid]\n");
    printf("  /subscribe [team_uuid]\n");
    printf("  /subscribed ?[team_uuid]\n");
    printf("  /unsubscribe [team_uuid]\n");
    printf("  /use ?[team_uuid] ?[channel_uuid] ?[thread_uuid]\n");
    printf("  /create\n");
    printf("  /list\n");
    printf("  /info\n");
}
