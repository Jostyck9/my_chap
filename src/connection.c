/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** connection.c
*/

#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <ctype.h>
#include <string.h>
#include <arpa/inet.h>
#include "client.h"

void fill_udp(header_data_t *to, const uint16_t dest_port, \
const uint16_t src_port)
{
    if (to == NULL)
        return;
    to->udp_hdr.source = htons(src_port);
    to->udp_hdr.dest = htons(dest_port);
    to->udp_hdr.len = htons(strlen(to->data) + sizeof(struct udphdr));
    to->udp_hdr.check = 0;
}

void fill_ip(header_data_t *to, const char *src, const char *dst)
{
    struct sockaddr_in src_add = {0};
    struct sockaddr_in dst_add = {0};

    if (to == NULL || src == NULL || dst == NULL)
        return;
    inet_aton(src, &src_add.sin_addr);
    inet_aton(dst, &dst_add.sin_addr);
    to->ip_hdr.version = 4;
    to->ip_hdr.ihl = 5;
    to->ip_hdr.tos = 0;
    to->ip_hdr.tot_len = sizeof(struct iphdr) + \
sizeof(struct udphdr) + strlen(to->data);
    to->ip_hdr.id = 0;
    to->ip_hdr.frag_off = 1 << 6;
    to->ip_hdr.ttl = 64;
    to->ip_hdr.protocol = 17;
    to->ip_hdr.daddr = dst_add.sin_addr.s_addr;
    to->ip_hdr.saddr = src_add.sin_addr.s_addr;
    to->ip_hdr.check = 0;
}

bool use_send_to(int sock, header_data_t *data, const int port, \
const char *addr)
{
    struct sockaddr_in to;
    size_t len = 0;

    len = sizeof(data->ip_hdr) + sizeof(data->udp_hdr) + strlen(data->data);
    memset(&to, 0, sizeof(to));
    to.sin_family = AF_INET;
    inet_aton(addr, &to.sin_addr);
    to.sin_port = htons(port);
    if (sendto(sock, data, len, 0, (struct sockaddr*)&to, sizeof(to)) == -1) {
        perror("sendto");
        return (false);
    }
    return (true);
}

char *use_recv_from(int sock, const int port, const char *addr)
{
    header_data_t *recv;
    char buffer[4000];
    int n = 0;
    struct sockaddr_in recv2 = {0};

    do {
        n = recvfrom(sock, buffer, 4000, 0, NULL, NULL);
        if (n == -1)
            return (NULL);
        recv = (header_data_t *)buffer;
        buffer[n] = '\0';
        recv2.sin_addr.s_addr = recv->ip_hdr.saddr;
    } while (strcmp(inet_ntoa(recv2.sin_addr), addr) != 0 || \
htons(recv->udp_hdr.source) != port);
    return (strdup(recv->data));
}

char *exchange_message(int sock, char *msg, const int port, const char *addr)
{
    header_data_t to_fill = { 0 };
    char *src = local_ip();
    char *recv = NULL;

    if (src == NULL)
        return (NULL);
    strcpy(to_fill.data, msg);
    fill_udp(&to_fill, port, 255);
    fill_ip(&to_fill, src, addr);
    if (use_send_to(sock, &to_fill, port, addr) == false)
        return (NULL);
    recv = use_recv_from(sock, port, addr);
    return (recv);
}