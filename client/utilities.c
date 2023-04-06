/*
** EPITECH PROJECT, 2023
** utilities.c
** File description:
** utilities
*/

#include "client.h"

char *clean_text(char *text)
{
    char *new_text = malloc(sizeof(char) * strlen(text));
    int i = 0;
    int j = 0;
    while (text[i] != '\0') {
        if (text[i] != '"') {
            new_text[j] = text[i];
            j++;
        }
        i++;
    }
    new_text[j] = '\0';
    return new_text;
}
