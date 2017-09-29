#ifndef Q_UTILS_H
#define Q_UTILS_H

#include <stdbool.h>

#define Q_VPTR_TO_INT(p) (*(int*)(p))

#ifdef __cplusplus
extern "C" {
#endif
    
    void die(const char*text);
    void *xmalloc(size_t size);
    void *xmalloc0(size_t size);
    void *xcalloc(size_t nmemb, size_t size);
    
    typedef bool (*less_fn)(void *lhs, void *rhs);

#ifdef __cplusplus
}
#endif

#endif /* Q_UTILS_H */

