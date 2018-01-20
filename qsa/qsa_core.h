#ifndef QSA_CORE_H
#define QSA_CORE_H

#include <stdbool.h>

#define QSA_OK 0
#define QSA_ERROR -1

#define QSA_VPTR_TO_INT(p) (*(int*)(p))
#define QSA_VPTR_TO_LONG(p) (*(long*)(p))

#define QSA_FOREVER() while(1)

#define UNUSED(x) ((void)(x))

#define QSA_LOG_ERR(...) fprintf(stderr, __VA_ARGS__)
#define QSA_LOG_INFO(...) printf(__VA_ARGS__)

void qsa_die(const char*msg);

void *qsa_malloc(size_t size);
void *qsa_malloc0(size_t size);
void *qsa_calloc(size_t nmemb, size_t size);

typedef int (qsa_compare_fn) (const void *l, const void *r);
typedef bool (qsa_equals_fn) (const void *l, const void *r);
typedef void (qsa_action_fn) (void *data);

typedef unsigned int (qsa_hash_fn) (const void *arg);

int qsa_compare_int(const void *l, const void *r);
bool qsa_equals_int(const void *l, const void *r);


#endif /* QSA_CORE_H */

