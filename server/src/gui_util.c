/*
** EPITECH PROJECT, 2024
** server
** File description:
** gui_util
*/

#include "../include/server.h"

/// @brief Send the given message to all grahic client connected
/// @param server Structure that contain all server data
/// @param txt Message send
static void send_guis_text(server_t *server, char *txt, va_list ap)
{
    client_t *client = NULL;

    va_end(ap);
    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (strcmp(client->client_type, GUI) == 0)
            send_client(client->fd, "%s", txt);
    }
    free(txt);
}

/// @brief Write formatted output to all GUI clients
/// @param server Structure that contain all server data
/// @param format Format of the message following printf function format
void send_to_all_gui(server_t *server, const char *format, ...)
{
    va_list ap;
    char *txt = malloc(sizeof(char) * BUFFER_SIZE);
    int n = 0;

    if (txt == NULL)
        return perror("send_to_all_gui");
    va_start(ap, format);
    for (int j = 0; format[j] != 0; j++) {
        if (format[j] == '%' && format[j + 1] == 's')
            n += sprintf(&txt[n], "%s", va_arg(ap, char *));
        if (format[j] == '%' && format[j + 1] == 'c')
            n += sprintf(&txt[n], "%c", va_arg(ap, int));
        if (format[j] == '%' && (format[j + 1] == 'd' || format[j + 1] == 'j'))
            n += sprintf(&txt[n], "%d", va_arg(ap, int));
        if (format[j] == '%')
            j += 1;
        else
            n += sprintf(&txt[n], "%c", format[j]);
    }
    send_guis_text(server, txt, ap);
}

/// @brief Select the File descriptor to apply dprintf on it
/// @param client_fd Client File Descriptor
/// @param txt Text to send
static void dprintf_with_select(int client_fd, char *txt, va_list ap)
{
    int ret = 0;
    int tmp = 0;
    fd_set fd;
    struct timeval time;

    va_end(ap);
    time.tv_sec = 0;
    time.tv_usec = 500;
    FD_ZERO(&fd);
    FD_SET(client_fd, &fd);
    tmp = select(client_fd + 1, NULL, &fd, NULL, &time);
    if (tmp == 1)
        ret = write(client_fd, txt, strlen(txt));
    if (ret == -1 || tmp == -1)
        perror("dprintf_with_select");
    free(txt);
}

/// @brief Write formatted output to the File Descriptor but with a select
/// @param server Structure that contain all server data
/// @param format Format of the message following printf function format
void send_client(int fd, const char *format, ...)
{
    va_list ap;
    char *txt = malloc(sizeof(char) * 256);
    int n = 0;

    if (txt == NULL)
        return perror("send_client");
    va_start(ap, format);
    for (int j = 0; format[j] != 0; j++) {
        if (format[j] == '%' && format[j + 1] == 's')
            n += sprintf(&txt[n], "%s", va_arg(ap, char *));
        if (format[j] == '%' && format[j + 1] == 'c')
            n += sprintf(&txt[n], "%c", va_arg(ap, int));
        if (format[j] == '%' && (format[j + 1] == 'd' || format[j + 1] == 'j'))
            n += sprintf(&txt[n], "%d", va_arg(ap, int));
        if (format[j] == '%')
            j += 1;
        else
            n += sprintf(&txt[n], "%c", format[j]);
    }
    dprintf_with_select(fd, txt, ap);
}
