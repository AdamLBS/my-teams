/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-florian.grima [WSL: Debian]
** File description:
** messages_history
*/

#include "client.h"

void send_messages_command(char *buffer, struct client *client)
{
    send(client->sock, buffer, strlen(buffer), 0);
    send(client->sock, "\n", 1, 0);
}

void receive_messages_history(char *buffer, struct client *client)
{
    uuid_t uuid;
    int error = strstr(buffer, "ERROR\n") != NULL;
    for (int i = 0; i != 13; i++, buffer++);
    char *token = strtok(buffer, " ");
    char *full_msg = malloc(sizeof(char) * MAX_BODY_LENGTH);
    memset(full_msg, 0, MAX_BODY_LENGTH);
    for (int i = 0; token != NULL &&
    uuid_parse(token, uuid) && strstr(token, "ERROR\n") == NULL; i++) {
        strcat(full_msg, token);
        strcat (full_msg, " ");
        token = strtok(NULL, " ");
    }
    char *id = token;
    if (error) {
        client_error_unknown_user(full_msg);
        return;
    }
    token = strtok(NULL, " ");
    print_history(token, id, full_msg, client);
}

void print_history(char *token, char *id, char *msg, struct client *client)
{
    char *timestamp = malloc(sizeof(char) * 150);
    memset(timestamp, 0, 150);
    for (int i = 0; i != 5; i++) {
        strcat(timestamp, token);
        strcat(timestamp, " ");
        token = strtok(NULL, " ");
    }
    char *isSender = token;
    time_t currentTime = time( NULL );
    struct tm * timeInfos = localtime( & currentTime );
    struct tm tm;
    tm.tm_isdst = timeInfos->tm_isdst;
    strptime(timestamp, "%a %b %d %H:%M:%S %Y", &tm);
    time_t t = mktime(&tm);
    if (isSender[0] == '0')
        client_private_message_print_messages(id, t, msg);
    else
        client_private_message_print_messages(client->id, t, msg);
    free(timestamp); free(msg);
}
