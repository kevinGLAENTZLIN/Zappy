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

/// @brief Read in the given File Descriptor and cut the String at the first
/// delimiter found
/// @param fd File Descriptor to read
/// @param delimiter Delimiter to cut at
/// @return NULL if read is empty or if an error occurred, else the read string
/// if the delimiter has been found, else "Buffer reading: KO"
char *read_to_buffer(int fd, char delimiter)
{
    char buffer[BUFFER_SIZE + 1];
    char *tmp = NULL;
    ssize_t size;

    size = read(fd, buffer, BUFFER_SIZE);
    if (size == -1 || size == 0)
        return NULL;
    buffer[size] = 0;
    if (is_in_str(delimiter, buffer)) {
        tmp = strndup(buffer, get_index_in_str(buffer, delimiter) + 1);
    } else {
        tmp = strdup("Buffer reading: KO");
    }
    return tmp;
}
