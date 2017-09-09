#ifndef Q_UTILS_H
#define Q_UTILS_H

#define Q_INT_TO_VOIDPTR(i) ((void*) (long) (i))
#define Q_VOIDPTR_TO_INT(p) ((int)(long)(p))

#ifdef __cplusplus
extern "C" {
#endif
    
    void die(const char*text);
    void *xmalloc(size_t size);
    void *xmalloc0(size_t size);
    void *xcalloc(size_t nmemb, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* Q_UTILS_H */

