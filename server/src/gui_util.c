/*
** EPITECH PROJECT, 2024
** server
** File description:
** gui_util
*/

#include "../include/server.h"

static void send_guis_text(server_t *server, char *txt)
{
    for (int i = 0; i < server->nb_client; i++) {
        if (strcmp(CLIENT_TYPE, GUI) == 0)
            dprintf(FD_CLIENT, "%s", txt);
    }
    free(txt);
}

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
