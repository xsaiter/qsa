#include <stdio.h>
#include <stdlib.h>

#include "qsa_utils.h"

#define FNV_32_PRIME (0x01000193)

inline void die(const char *text)
{
    perror(text);
    exit(EXIT_FAILURE);
}

void *xmalloc(size_t size)
{
    void *p = malloc(size);
    if (!p) {
        die("xmalloc");
    }
    return p;
}

void *xmalloc0(size_t size)
{

    void *p = calloc(1, size);
    if (!p) {
        die("xmalloc0");
    }
    return p;
}

void *xcalloc(size_t nmemb, size_t size)
{
    void *p = calloc(nmemb, size);
    if (!p) {
        die("xcalloc");
    }
    return p;
}

int q_compare_int(const void *l, const void *r)
{
    int lv = Q_VPTR_TO_INT(l);
    int rv = Q_VPTR_TO_INT(r);

    if (lv > rv) {
        return 1;
    }
    if (lv < rv) {
        return -1;
    }
    return 0;
}

bool q_equals_int(const void *l, const void *r)
{
    return q_compare_int(l, r) == 0;
}

unsigned int q_hash_str(const void *arg)
{    
    return fnv1_hash((char*)arg);
}

unsigned int fnv1_hash(char *buf)
{
    unsigned int hval = 0x811c9dc5;

    while (*buf) {
        hval ^= (unsigned int) *buf++;
        hval *= FNV_32_PRIME;
    }

    return hval;
}