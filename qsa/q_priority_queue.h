#ifndef Q_PRIORITY_QUEUE_H
#define Q_PRIORITY_QUEUE_H

#include "q_list.h"
#include "q_utils.h"

#ifdef __cplusplus
extern "C" {
#endif
       
    
    typedef struct{
        q_list *list;
        less_fn *compare;
    } q_priority_queue;
    
    q_priority_queue *q_priority_queue_new(int data_size);
    void q_priority_queue_free(q_priority_queue *q);
    void q_priority_queue_add(q_priority_queue *q, void *data);
    void *q_priority_queue_extract(q_priority_queue *q);

#ifdef __cplusplus
}
#endif

#endif /* Q_PRIORITY_QUEUE_H */

