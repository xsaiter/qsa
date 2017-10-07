#ifndef Q_UTILS_H
#define Q_UTILS_H

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
    int q_compare_int(const void *l, const void *r);

#ifdef __cplusplus
}
#endif

#endif /* Q_UTILS_H */

