/*
** EPITECH PROJECT, 2024
** server
** File description:
** buffer
*/

#include "../include/buffer.h"

/// @brief Check if the character C is contained in the string STR
/// @param c Character to find
/// @return True if found, else False
bool is_in_str(char c, const char *str)
{
    if (str == NULL)
        return false;
    for (int i = 0; str[i] != 0; i++)
        if (str[i] == c)
            return true;
    return false;
}

/// @brief Check if the character C is contained in the string STR
/// @param c Character to find
/// @return Index of the first C found, else -1
static int get_index_in_str(const char *str, int c)
{
    if (str == NULL)
        return -1;
    for (int i = 0; str[i] != 0; i++)
        if (str[i] == c)
            return i;
    return -1;
}

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

    if (word == NULL) {
        perror("word_cpy");
        return NULL;
    }
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
char **my_str_to_word_array(char const *str, char const *delim)
{
    char **array = malloc(sizeof(char *) * (get_nbr_word(str, delim) + 1));
    int word_size = 0;
    int i_str = 0;
    int i_array = 0;

    if (array == NULL) {
        perror("my_str_to_word_array");
        return NULL;
    }
    while (str[i_str] != '\0') {
        if (is_in_str(str[i_str], delim) == 0) {
            word_size = count_word_size(str, i_str, delim);
            array[i_array] = word_cpy(str, word_size, i_str);
            array[i_array][word_size] = '\0';
            array[i_array][word_size + 1] = '\0';
            i_str += word_size;
            i_array++;
        } else
            i_str++;
    }
    array[get_nbr_word(str, delim)] = NULL;
    return array;
}

/// @brief Read in the given File Descriptor and cut the String at the first
/// delimiter found
/// @param fd File Descriptor to read
/// @param delimiter Delimiter to cut at
/// @return NULL if read is empty or if an error occurred, else the read string
/// if the delimiter has been found, else "Buffer reading: KO"
char **read_to_buffer(int fd, char delimiter)
{
    char buffer[BUFFER_SIZE + 1];
    char delim[2];
    char **tmp = NULL;
    ssize_t size;

    size = read(fd, buffer, BUFFER_SIZE);
    if (size == -1 || size == 0)
        return NULL;
    buffer[size] = 0;
    delim[0] = delimiter;
    delim[1] = 0;
    if (is_in_str(delimiter, buffer)) {
        return my_str_to_word_array(buffer, delim);
    }
    tmp = malloc(sizeof(char *) * 2);
    tmp[0] = strdup(BUFFER_ERR);
    tmp[1] = NULL;
    return tmp;
}
