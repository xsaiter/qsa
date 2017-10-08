#include <stdlib.h>
#include "q_dict.h"

#define Q_DICT_TABLE_SIZE (16)

q_dict *q_dict_new(q_hash_fn *hash_key, q_equals_fn *equals_key)
{
    q_dict *d = xmalloc(sizeof (q_dict));

    d->table_size = Q_DICT_TABLE_SIZE;
    d->nelems = 0;
    d->hash_key = hash_key;
    d->equals_key = equals_key;

    d->table = xmalloc(d->table_size * sizeof (void*));
    for (int i = 0; i < d->table_size; ++i) {
        d->table[i] = NULL;
    }

    return d;
}

inline static unsigned int idx_table(q_dict *d, const void *key)
{
    unsigned int h = d->hash_key(key);
    return h % d->table_size;
}

static q_dict_elem *q_find_elem(q_dict *d, const void *key)
{
    q_dict_elem *e = d->table[idx_table(d, key)];
    while (e && !(d->equals_key(e->key, key))) {
        e = e->next;
    }
    return e;
}

q_dict_elem *elem_new(q_dict *d, void *key, void *value)
{
    q_dict_elem *e = xmalloc(sizeof (q_dict_elem));

    e->key = key;
    e->value = value;
    e->hash = d->hash_key(key);
    e->next = NULL;

    return e;
}

void q_dict_add(q_dict *d, void *key, void *value)
{
    unsigned int idx = idx_table(d, key);
    q_dict_elem *e = d->table[idx];
    if (!e) {
        d->table[idx] = elem_new(d, key, value);
    } else {
        q_dict_elem *x = e;
        while (x && !(d->equals_key(e->key, key))) {
            x = x->next;
        }
        
        if (!x) {
            q_dict_elem *s = elem_new(d, key, value);
            s->next = d->table[idx];
            d->table[idx] = s;

        }
    }
}

void *q_dict_get(q_dict *d, const void *key)
{
    q_dict_elem *e = q_find_elem(d, key);
    if (e) {
        return e->value;
    }
    return NULL;
}