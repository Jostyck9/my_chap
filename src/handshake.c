/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** handshake.c
*/

#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "client.h"

int create_socket(void)
{
    int sock = -1;
    int option = 1;

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sock == -1) {
        perror("sock()");
        return (-1);
    }
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, \
(char *)&option, sizeof(option)) == -1) {
        perror("setsockopt()");
        close(sock);
        return (-1);
    }
    return (sock);
}

bool phase_exchange(int sock, const int port, const char *addr, \
const char *pass)
{
    char *answer = NULL;
    char *to_send = NULL;

    answer = exchange_message(sock, "client hello", port, addr);
    if (answer == NULL)
        return (false);
    to_send = get_sha_with_pass(answer, pass);
    free(answer);
    if (to_send == NULL)
        return (false);
    answer = exchange_message(sock, to_send, port, addr);
    free(to_send);
    if (answer == NULL)
        return (false);
    if (strcmp(answer, "KO") == 0) {
        printf("KO\n");
    } else {
        printf("Secret: \'%s\'\n", answer);
    }
    free(answer);
    return (true);
}

bool handshake(arg_client_t args)
{
    int sock = -1;
    bool res = true;

    if (args.pass == NULL || args.ip == NULL || args.port == 0)
        return (false);
    sock = create_socket();
    if (sock == -1)
        return (false);
    res = phase_exchange(sock, args.port, args.ip, args.pass);
    close(sock);
    return (res);
}