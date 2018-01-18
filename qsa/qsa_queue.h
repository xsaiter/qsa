#ifndef _QSA_QUEUE_H
#define _QSA_QUEUE_H

#include "qsa_list.h"

#ifdef __cplusplus
extern "C" {
#endif    

    typedef struct {
        q_list *list;
    } q_queue;
        
    q_queue *q_queue_new(size_t data_size);        
    void q_queue_free(q_queue *q);
    void q_queue_enq(q_queue *q, void *data);
    void *q_queue_deq(q_queue *q);
    bool q_queue_empty(q_queue *q);
    
    q_queue *q_queue_new_int();

#ifdef __cplusplus
}
#endif

#endif /* _QSA_QUEUE_H */
