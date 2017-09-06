#ifndef Q_VECTOR_H
#define Q_VECTOR_H

#include<stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        void **elems;        
        size_t len;
        size_t capacity;
    } q_vector;
    
    void q_vector_init(q_vector *v, size_t capacity);
    void q_vector_destroy(q_vector *v);
    void q_vector_add(q_vector *v, void *elem);    
    void q_vector_set(q_vector *v, size_t index, void *elem);
    void *q_vector_get(q_vector *v, size_t index);
    void q_vector_for_each(q_vector *v, void (*f)(void* elem));

#ifdef __cplusplus
}
#endif

#endif /* Q_VECTOR_H */

