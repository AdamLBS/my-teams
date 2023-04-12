/*
** EPITECH PROJECT, 2023
** put.c
** File description:
** put
*/

#include "server.h"

void put_r(struct reply *reply, char *uuid, char *tm_uuid, char *t_uuid)
{
    reply->t_uuid = strdup(t_uuid);
    reply->tm_uuid = strdup(tm_uuid);
    reply->o_uuid = strdup(uuid);
    create_reply_file(reply);
}

void put_s(struct thread *thread, char *time, char *t_uuid, char *o_uuid)
{
    thread->o_uuid = strdup(o_uuid);
    thread->t_uuid = strdup(t_uuid);
    thread->time = strdup(time);
    thread->replies = malloc(sizeof(struct reply *) * 100);
    create_thread_file(thread);
}
