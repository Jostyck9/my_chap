/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** arg_management.c
*/

#include <string.h>
#include "client.h"

bool get_pass(char *arg, arg_client_t *to_fill)
{
    if (to_fill->pass != NULL) {
        dprintf(2, "-P: Password already given\n");
        return (false);
    }
    to_fill->pass = strdup(arg);
    return (true);
}

bool get_port(char *arg, arg_client_t *to_fill)
{
    if (to_fill->port != 0) {
        dprintf(2, "-p: Port already given\n");
        return (false);
    }
    to_fill->port = atoi(arg);
    if (to_fill->port == 0 || to_fill->port > 65335) {
        dprintf(2, "Invalid port\n");
        return (false);
    }
    return (true);
}

bool get_target(char *arg, arg_client_t *to_fill)
{
    if (to_fill->ip != NULL) {
        dprintf(2, "-t: Target already given\n");
        return (false);
    }
    to_fill->ip = arg;
    if (resolve_hostname(to_fill) == false)
        return (false);
    return (true);
}

bool get_current_para(char **av, arg_client_t *to_fill)
{
    if (strcmp(av[0], "-t") == 0 || strcmp(av[0], "--target") == 0)
        return (get_target(av[1], to_fill));
    if (strcmp(av[0], "-p") == 0 || strcmp(av[0], "--port") == 0)
        return (get_port(av[1], to_fill));
    if (strcmp(av[0], "-P") == 0 || strcmp(av[0], "--password") == 0)
        return (get_pass(av[1], to_fill));
    dprintf(2, "Unknown parameter : %s\n", av[0]);
    return (false);
}

bool get_args(int ac, char **av, arg_client_t *to_fill)
{
    if (av == NULL || to_fill == NULL || ac != 7) {
        dprintf(2, "Invalid parameters\n");
        return (false);
    }
    for (int i = 1; i < ac; i += 2) {
        if (get_current_para(&av[i], to_fill) == false) {
            return (false);
        }
    }
    return (true);
}