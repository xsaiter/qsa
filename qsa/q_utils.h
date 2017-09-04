#ifndef Q_UTILS_H
#define Q_UTILS_H

#define Q_INT_TO_VOIDPTR(i) ((void*) (int) (i))
#define Q_VOIDPTR_TO_INT(p) ((int)(long)(p))

#ifdef __cplusplus
extern "C" {
#endif
    
    void die(const char*text);     

#ifdef __cplusplus
}
#endif

#endif /* Q_UTILS_H */

