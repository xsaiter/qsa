#include <stdio.h>
#include <stdlib.h>

#include "qsa_core.h"

inline void qsa_die(const char *text)
{
    perror(text);
    exit(EXIT_FAILURE);
}

void *qsa_malloc(size_t size)
{
    void *p = malloc(size);
    if (!p) {
        qsa_die("xmalloc");
    }
    return p;
}

void *qsa_malloc0(size_t size)
{

    void *p = calloc(1, size);
    if (!p) {
        qsa_die("xmalloc0");
    }
    return p;
}

void *qsa_calloc(size_t nmemb, size_t size)
{
    void *p = calloc(nmemb, size);
    if (!p) {
        qsa_die("xcalloc");
    }
    return p;
}

int qsa_compare_int(const void *l, const void *r)
{
    int lv = QSA_VPTR_TO_INT(l);
    int rv = QSA_VPTR_TO_INT(r);

    if (lv > rv) {
        return 1;
    }

    if (lv < rv) {
        return -1;
    }

    return 0;
}

bool qsa_equals_int(const void *l, const void *r)
{
    return qsa_compare_int(l, r) == 0;
}