#include <stdlib.h>
#include <string.h>
#include "q_dict.h"

#define Q_DICT_TABLE_SIZE (16)

q_dict *q_dict_new(size_t key_size, q_hash_fn *key_hash, q_equals_fn *key_equals, size_t value_size)
{
    q_dict *d = xmalloc(sizeof (q_dict));

    d->key_size = key_size;
    d->key_hash = key_hash;
    d->key_equals = key_equals;

    d->value_size = value_size;

    d->table_size = Q_DICT_TABLE_SIZE;

    d->table = xmalloc(d->table_size * sizeof (void*));
    for (int i = 0; i < d->table_size; ++i) {
        d->table[i] = NULL;
    }

    return d;
}

inline static unsigned int idx_table(q_dict *d, const void *key)
{
    unsigned int h = d->key_hash(key);
    return h % d->table_size;
}

static q_dict_elem *q_find_elem(q_dict *d, const void *key)
{
    q_dict_elem *e = d->table[idx_table(d, key)];
    while (e && !(d->key_equals(e->key, key))) {
        e = e->next;
    }
    return e;
}

q_dict_elem *elem_new(q_dict *d, void *key, void *value)
{
    q_dict_elem *e = xmalloc(sizeof (q_dict_elem));

    e->key = xmalloc(d->key_size);
    memcpy(e->key, key, d->key_size);

    e->value = xmalloc(d->value_size);
    memcpy(e->value, value, d->value_size);    

    e->hash = d->key_hash(key);
    e->next = NULL;

    return e;
}

void q_dict_free(q_dict *d)
{
    free(d);
}

void q_dict_add(q_dict *d, void *key, void *value)
{
    unsigned int idx = idx_table(d, key);
    q_dict_elem *e = d->table[idx];
    if (!e) {
        d->table[idx] = elem_new(d, key, value);
    } else {
        q_dict_elem *x = e;
        while (x && !(d->key_equals(e->key, key))) {
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