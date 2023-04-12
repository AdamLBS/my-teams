/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Ubuntu]
** File description:
** update_structs
*/

#include "server.h"

void update_thread_struct(struct thread *thr, char *t_uuid)
{
    thr->uuid = strdup(t_uuid); thr->replies = malloc(sizeof(reply_t *));
    thr->o_uuid = strdup(get_file_line_n(1, t_uuid, "./threads/"));
    thr->time = strdup(get_file_line_n(2, t_uuid, "./threads/"));
    thr->name = strdup(get_file_line_n(3, t_uuid, "./threads/"));
    thr->body = strdup(get_file_line_n(4, t_uuid, "./threads/"));
    thr->t_uuid = strdup(get_file_line_n(5, t_uuid, "./threads/"));
    thr->c_uuid = strdup(get_file_line_n(6, t_uuid, "./threads/"));
}