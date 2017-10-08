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
        q_dict_elem **table;           
        q_hash_fn *key_hash;
        q_equals_fn *key_equals;
        size_t key_size;
        size_t value_size;
    } q_dict;
    
    q_dict *q_dict_new(size_t key_size, q_hash_fn *key_hash, q_equals_fn *key_equals, size_t value_size);
    void q_dict_free(q_dict *d);
    void q_dict_add(q_dict *d, void *key, void *value);
    void *q_dict_get(q_dict *d, const void *key);

#ifdef __cplusplus
}
#endif

#endif /* Q_DICT_H */