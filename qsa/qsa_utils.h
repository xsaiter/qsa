#ifndef QSA_UTILS_H
#define QSA_UTILS_H

#include <stdbool.h>

#define Q_VPTR_TO_INT(p) (*(int*)(p))
#define Q_VPTR_TO_LONG(p) (*(long*)(p))

#ifdef __cplusplus
extern "C" {
#endif

    void die(const char*text);    
    void *xmalloc(size_t size);    
    void *xmalloc0(size_t size);    
    void *xcalloc(size_t nmemb, size_t size);

    typedef int (q_compare_fn) (const void *l, const void *r);
    typedef bool (q_equals_fn) (const void *l, const void *r);
    
    typedef unsigned int (q_hash_fn)(const void *arg);
    
    int q_compare_int(const void *l, const void *r);
    bool q_equals_int(const void *l, const void *r);
    unsigned int q_hash_str(const void *arg);
    
    unsigned int fnv1_hash(char *buf);

#ifdef __cplusplus
}
#endif

#endif /* QSA_UTILS_H */

