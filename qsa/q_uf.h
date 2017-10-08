/*
 * union-find data structure (disjoint sets)
 */

#ifndef Q_UF_H
#define Q_UF_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_uf_node {
        struct q_uf_node *parent;
        int rank;
        void *value;
    } q_uf_node;

    typedef struct {
        q_uf_node *nodes;
        int nnodes;
        size_t value_size;
    } q_uf;

#ifdef __cplusplus
}
#endif

#endif /* Q_UF_H */
