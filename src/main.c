/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** main.c
*/

#include "client.h"

void delete_arg(arg_client_t *args)
{
    if (args == NULL)
        return;
    if (args->ip != NULL) {
        free(args->ip);
        args->ip = NULL;
    }
    if (args->pass != NULL) {
        free(args->pass);
        args->pass = NULL;
    }
}

int main(int ac, char **av)
{
    arg_client_t to_fill = { 0 };
    int return_value = 0;

    to_fill.ip = NULL;
    to_fill.port = 0;
    to_fill.pass = NULL;
    if (get_args(ac, av, &to_fill) == false) {
        delete_arg(&to_fill);
        return (84);
    }
    if (handshake(to_fill) == false)
        return_value = 84;
    delete_arg(&to_fill);
    return (return_value);
}