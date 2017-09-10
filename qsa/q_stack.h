#ifndef Q_STACK_H
#define Q_STACK_H

#include <stdbool.h>

#include "q_list.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct{
        q_list *list;
    } q_stack;   
    
    q_stack *q_stack_new();
    void q_stack_free(q_stack *s);
    bool q_stack_empty(q_stack *s);
    void q_stack_push(q_stack *s, void *data);
    void *q_stack_pop(q_stack *s);
        
#ifdef __cplusplus
}
#endif

#endif /* Q_STACK_H */

