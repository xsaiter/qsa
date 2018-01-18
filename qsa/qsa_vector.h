#ifndef _QSA_VECTOR_H
#define _QSA_VECTOR_H

#include<stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        void **elems;        
        size_t len;
        size_t capacity;
        size_t elem_size;
    } q_vector;
        
    q_vector *q_vector_new(size_t capacity, size_t elem_size);
    void q_vector_free(q_vector *v);
    void q_vector_add(q_vector *v, void *elem);
    void q_vector_set(q_vector *v, size_t index, void *elem);
    void *q_vector_get(q_vector *v, size_t index);
    void q_vector_for_each(q_vector *v, void (*f)(void* elem));
    
    q_vector *q_vector_new_int(size_t capacity);

#ifdef __cplusplus
}
#endif

#endif /* _QSA_VECTOR_H */

