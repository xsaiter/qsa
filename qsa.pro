QMAKE_CC = gcc -std=c11

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        qsa/qsa_core.c \
        qsa/qsa_avl.c \
        qsa/qsa_bst.c \
        qsa/qsa_btree.c \
        qsa/qsa_dict.c \
        qsa/qsa_fib_heap.c \
        qsa/qsa_heap.c \
        qsa/qsa_list.c \
        qsa/qsa_queue.c \
        qsa/qsa_rbt.c \
        qsa/qsa_sort.c \
        qsa/qsa_stack.c \
        qsa/qsa_uf.c \
        qsa/qsa_utils.c \
        qsa/qsa_van_eb_tree.c \
        qsa/qsa_vector.c \
        qsa/geo/qsa_convex_hull.c \
        qsa/geo/qsa_geo.c \
        qsa/str/qsa_str.c \
        qsa/graphs/qsa_graph.c \
        qsa/graphs/qsa_kruskal.c \
        qsa/graphs/qsa_lee_alg.c \
        qsa/graphs/qsa_prim.c \
        qsa/graphs/qsa_dijkstra.c \
        main.c

HEADERS += \
        qsa/qsa_core.h \
        qsa/qsa_avl.h \
        qsa/qsa_bst.h \
        qsa/qsa_btree.h \
        qsa/qsa_dict.h \
        qsa/qsa_fib_heap.h \
        qsa/qsa_heap.h \
        qsa/qsa_list.h \
        qsa/qsa_queue.h \
        qsa/qsa_rbt.h \
        qsa/qsa_sort.h \
        qsa/qsa_stack.h \
        qsa/qsa_uf.h \
        qsa/qsa_utils.h \
        qsa/qsa_van_eb_tree.h \
        qsa/qsa_vector.h \
        qsa/geo/qsa_convex_hull.h \
        qsa/geo/qsa_geo.h \
        qsa/str/qsa_str.h \
        qsa/graphs/qsa_graph.h \
        qsa/graphs/qsa_mst.h \
        qsa/graphs/qsa_lee_alg.h \
        qsa/graphs/qsa_dijkstra.h \
