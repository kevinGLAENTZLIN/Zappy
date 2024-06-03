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
static void send_guis_text(server_t *server, char *txt)
{
    client_t *client = NULL;

    for (int i = 0; i < server->nb_client; i++) {
        client = CLIENT;
        if (strcmp(client->client_type, GUI) == 0)
            dprintf(client->fd, "%s", txt);
    }
    free(txt);
}

/// @brief Write formatted output to all GUI clients
/// @param server Structure that contain all server data
/// @param format Format of the message following printf function format
void send_to_all_gui(server_t *server, const char *format, ...)
{
    va_list ap;
    char *txt = malloc(sizeof(char) * 1024);
    int n = 0;

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
    va_end(ap);
    send_guis_text(server, txt);
}
