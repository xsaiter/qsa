#ifndef Q_QUEUE_H
#define Q_QUEUE_H

#include "q_list.h"

#ifdef __cplusplus
extern "C" {
#endif    

    typedef struct {
        q_list *list;
    } q_queue;
    
    q_queue *q_queue_new();    
    void q_queue_free(q_queue *q);
    void q_queue_enq(q_queue *q, void *data);
    void *q_queue_deq(q_queue *q);
    bool q_queue_empty(q_queue *q);

#ifdef __cplusplus
}
#endif

#endif /* Q_QUEUE_H */

