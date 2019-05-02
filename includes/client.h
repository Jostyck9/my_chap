/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** client.h
*/

#ifndef CLIENT_H_
#define CLIENT_H_

#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct header_data_s {
    struct iphdr ip_hdr;
    struct udphdr udp_hdr;
    char data[4000];
};
typedef struct header_data_s header_data_t;

struct arg_client_s {
    char *ip;
    unsigned int port;
    char *pass;
};
typedef struct arg_client_s arg_client_t;

bool resolve_hostname(arg_client_t *args);
bool get_args(int ac, char **av, arg_client_t *to_fill);
bool handshake(arg_client_t args);
char *exchange_message(int sock, char *msg, const int port, const char *addr);
char *get_sha_with_pass(const char *anwser, const char *key);
uint16_t checksum(const void *addr, int count);
char *local_ip(void);

#endif //CLIENT_H_