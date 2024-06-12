/*
** EPITECH PROJECT, 2024
** server
** File description:
** util
*/

#include "../include/server.h"

/// @brief Split the Client input
char **get_parameters(char *input)
{
    return my_str_to_word_array(input, " \n\r");
}

/// @brief Free the given string tab
void free_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

/// @brief Return the number of element between the start of the list and the
/// given delimiter
/// @param delimiter Delimiter at the end of the list
/// @param elts List of elements
/// @return Number of elements
int my_len(void *delimiter, void **elts)
{
    int i = 0;

    if (elts == delimiter)
        return 0;
    for (; elts[i] != delimiter; i++);
    return i;
}
