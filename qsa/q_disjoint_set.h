#ifndef Q_DISJOINT_SET_H
#define Q_DISJOINT_SET_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_disjoint_set_item {
        int rank;
        void *value;
        struct q_disjoint_set_item *parent;
    } q_disjoint_set_item;

    typedef struct {
        q_disjoint_set_item *items;
    };

#ifdef __cplusplus
}
#endif

#endif /* Q_DISJOINT_SET_H */

