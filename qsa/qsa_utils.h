#ifndef QSA_UTILS_H
#define QSA_UTILS_H

#include <stdbool.h>

#define QSA_VPTR_TO_INT(p) (*(int*)(p))
#define QSA_VPTR_TO_LONG(p) (*(long*)(p))

#ifdef __cplusplus
extern "C" {
#endif

    void qsa_die(const char*text);    
    void *qsa_malloc(size_t size);    
    void *qsa_malloc0(size_t size);    
    void *qsa_calloc(size_t nmemb, size_t size);

    typedef int (qsa_compare_fn) (const void *l, const void *r);
    typedef bool (qsa_equals_fn) (const void *l, const void *r);
    
    typedef unsigned int (qsa_hash_fn)(const void *arg);
    
    int qsa_compare_int(const void *l, const void *r);
    bool qsa_equals_int(const void *l, const void *r);
    unsigned int qsa_hash_str(const void *arg);
    
    unsigned int qsa_fnv1_hash(char *buf);

#ifdef __cplusplus
}
#endif

#endif /* QSA_UTILS_H */

