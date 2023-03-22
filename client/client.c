/*
** EPITECH PROJECT, 2023
** client.c
** File description:
** client
*/

#include "client.h"

void *get_lib(void)
{
    void *handle = dlopen("./libs/myteams/libmyteams.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    return handle;
}

void set_struct_client(client_t *cl)
{
    cl->username = malloc(sizeof(char) * MAX_NAME_LENGTH);
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_unparse(uuid, cl->id);
}

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    if (dummy == SIGINT)
        keepRunning = 0;
}

void create_client(char *ip, char *port)
{
    void *handle = get_lib();
    client_t client;
    client.sock = socket(AF_INET, SOCK_STREAM, 0);
    set_struct_client(&client);
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    inet_aton(ip, &myaddr.sin_addr);
    myaddr.sin_port = htons(atoi(port));
    connect(client.sock, (struct sockaddr *)&myaddr, sizeof(myaddr));
    write(client.sock, client.id, strlen(client.id));
    // signal(SIGINT, intHandler);
    while (1) {
        send_commands(handle, &client);
    }
    dlclose(handle);
}
