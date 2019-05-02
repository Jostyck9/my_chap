/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** resolve_hostname.c
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#include "client.h"

bool is_ip(char *str)
{
    int nbr_point = 0;

    if (str == NULL)
        return (false);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.' && str[i + 1] == '.')
            return (false);
        if (str[i] == '.')
            nbr_point++;
        else if (isdigit(str[i]) == false)
            return (false);
    }
    if (nbr_point != 3)
        return (false);
    return (true);
}

char *get_ip_from_host(char *host)
{
    struct hostent *res = NULL;
    struct in_addr **addr_list = NULL;

    if (host == NULL)
        return (NULL);
    res = gethostbyname(host);
    if (res == NULL)
        return (NULL);
    addr_list = (struct in_addr **)res->h_addr_list;
    if (addr_list[0] == NULL)
        return (NULL);
    return (strdup(inet_ntoa(*addr_list[0])));
}

char *strdup_ip(const char *ip)
{
    if (strcmp(ip, "127.0.0.1") != 0)
        return (strdup(ip));
    return (local_ip());
}

bool resolve_hostname(arg_client_t *args)
{
    char *save = NULL;

    if (args == NULL || args->ip == NULL)
        return (false);
    save = args->ip;
    if (is_ip(args->ip) == true) {
        args->ip = strdup_ip(args->ip);
        return (true);
    }
    args->ip = get_ip_from_host(args->ip);
    if (args->ip == NULL) {
        printf("No such hostname: \'%s\'\n", save);
        return (false);
    }
    if (strcmp(args->ip, "127.0.0.1") == 0) {
        free(args->ip);
        args->ip = local_ip();
    }
    return (true);
}

char *local_ip(void)
{
    struct ifaddrs *id;
    struct ifaddrs *tmp;
    char *res = NULL;

    if (getifaddrs(&id) == -1)
        return (NULL);
    tmp = id;
    while (tmp) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET && \
strcmp(tmp->ifa_name, "lo") != 0) {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            res = strdup(inet_ntoa(pAddr->sin_addr));
            break;
        }
        tmp = tmp->ifa_next;
    }
    freeifaddrs(id);
    if (res == NULL)
        return (strdup("127.0.0.1"));
    return (res);
}