/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** get_struct_data
*/


#include "server.h"

struct reply *get_reply_struct(struct team *team, int na, int nz, int i)
{
    team->channels[na]->threads[nz]->replies[i] = malloc(sizeof(struct reply));
    return team->channels[na]->threads[nz]->replies[i];
}

struct thread *get_thread_struct(struct team *team, int na, int i)
{
    team->channels[na]->threads[i] = malloc(sizeof(struct thread));
    return team->channels[na]->threads[i];
}
