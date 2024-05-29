/*
** EPITECH PROJECT, 2024
** server
** File description:
** util
*/

#include "../include/server.h"

static char *get_parameter(char *input, size_t index)
{
    char *str;
    int len = 0;

    for (; input[index] != '"' && input[index] != 0; index++);
    if (input[index] == 0 || input[index + 1] == 0)
        return NULL;
    index += 1;
    for (; input[index + len] != '"' && input[index + len] != 0; len++);
    if (input[index + len] == 0)
        return NULL;
    str = malloc(sizeof(char) * (len + 1));
    strncpy(str, &input[index], len);
    str[len] = 0;
    return str;
}

char **get_parameters(char *input)
{
    int count = 0;
    int index = 0;
    int i = 0;
    char **tab;

    for (int i = 0; input[i] != 0; i++)
        if (input[i] == '"')
            count += 1;
    if (count == 0 || count % 2 == 1)
        return NULL;
    tab = malloc(sizeof(char *) * (count / 2 + 1));
    for (; i < count / 2; i++) {
        for (; input[index] != '"' && input[index] != 0; index++);
        tab[i] = get_parameter(input, index);
        if (tab[i] != NULL)
            index += strlen(tab[i]) + 2;
    }
    tab[i] = NULL;
    return tab;
}

void free_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

int my_len(void *delimiter, void **elts)
{
    int i = 0;

    if (elts == delimiter)
        return 0;
    for (; elts[i] != delimiter; i++);
    return i;
}
