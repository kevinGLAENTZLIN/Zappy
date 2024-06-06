/*
** EPITECH PROJECT, 2024
** server
** File description:
** util
*/

#include "../include/server.h"

/// @brief Return the number of word separated by the given delimiter in the
/// given string
/// @param delim List of delimiter
/// @return Number of words
static int get_nbr_word(char const *str, char const *delim)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (i != 0 && is_in_str(str[i], delim) == 1 &&
            is_in_str(str[i - 1], delim) == 0)
            count++;
        i++;
    }
    if (is_in_str(str[i - 1], delim) == 0)
        count++;
    return count;
}

/// @brief Return the size of Ith word separated by the given delimiter in the
/// given string
/// @param delim List of delimiter
/// @param i_str Word index
/// @return Size of the words
static int count_word_size(char const *str, int i_str, char const *delim)
{
    int word_size = 1;

    while (str[i_str + word_size] != '\0' &&
            is_in_str(str[i_str + word_size], delim) == 0)
        word_size++;
    return word_size;
}

/// @brief Duplicate the Ith word separated by the given delimiter in the
/// given string
/// @param word_size Size of the words
/// @param i_str Index of the word
/// @return Pointer on the duplicate words
static char *word_cpy(char const *str, int word_size, int i_str)
{
    int i_word = 0;
    char *word = malloc(sizeof(char) * word_size + 2);

    while (i_word < word_size) {
        word[i_word] = str[i_str];
        i_str++;
        i_word++;
    }
    return word;
}

/// @brief Split the given string in fuction of the delimiters
/// @param str String to split
/// @param delim List of delimiter
/// @return List of words
static char **my_str_to_word_array(char const *str, char const *delim)
{
    int word_count = get_nbr_word(str, delim);
    char **word_array = malloc(sizeof(char *) * (word_count + 1));
    int word_size = 0;
    int i_str = 0;
    int i_array = 0;

    while (str[i_str] != '\0') {
        if (is_in_str(str[i_str], delim) == 0) {
            word_size = count_word_size(str, i_str, delim);
            word_array[i_array] = word_cpy(str, word_size, i_str);
            word_array[i_array][word_size] = '\0';
            word_array[i_array][word_size + 1] = '\0';
            i_str += word_size;
            i_array++;
        } else
            i_str++;
    }
    word_array[word_count] = NULL;
    return word_array;
}

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
