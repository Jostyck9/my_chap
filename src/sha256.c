/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** sha256.c
*/

#include <string.h>
#include <openssl/sha.h>
#include "client.h"

uint16_t checksum(const void *addr, int count)
{
    register uint32_t sum = 0;
    const uint16_t *ptr = addr;

    while (count > 1) {
        sum += *ptr++;
        count -= 2;
    }
    if (count > 0)
        sum += *(uint8_t *) ptr;
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);
    return (~sum);
}

char *get_sha256(const char *str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char *res = NULL;
    SHA256_CTX sha256;

    if (str == NULL)
        return (NULL);
    res = malloc(sizeof(*hash) * 65);
    if (res == NULL)
        return (NULL);
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((res + (i * 2)), "%02x", hash[i]);
    }
    return (res);
}

char *get_sha_with_pass(const char *anwser, const char *key)
{
    char *to_hash = NULL;
    char *res = NULL;

    if (anwser == NULL || key == NULL)
        return (NULL);
    to_hash = malloc(sizeof(char) * (strlen(anwser) + strlen(key) + 1));
    if (to_hash == NULL)
        return (NULL);
    strcpy(to_hash, anwser);
    strcat(to_hash, key);
    res = get_sha256(to_hash);
    free(to_hash);
    return (res);
}