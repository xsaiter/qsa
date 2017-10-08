#ifndef Q_DICT_H
#define Q_DICT_H

#include "q_utils.h"

extern void *dict_not_found;

#ifdef __cplusplus
extern "C" {
#endif        

    typedef struct q_dict_elem {
        void *key;
        void *value;
        struct q_dict_elem *next;
        unsigned int hash;
    } q_dict_elem;

    typedef struct {
        int table_size;
        int nelems;
        q_dict_elem **table;           
        q_hash_fn *hash_key;
        q_equals_fn *equals_key;
    } q_dict;
    
    q_dict *q_dict_new(q_hash_fn *hash_key, q_equals_fn *equals_key);
    void q_dict_free(q_dict *d);
    void q_dict_add(q_dict *d, void *key, void *value);
    void *q_dict_get(q_dict *d, const void *key);

#ifdef __cplusplus
}
#endif

#endif /* Q_DICT_H */