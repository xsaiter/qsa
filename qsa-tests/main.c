#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "q_list.h"
#include "q_utils.h"

#include "str/q_str.h"
#include "graphs/q_graph.h"

struct person {
    int age;
};

static void print_(void *data)
{
    char* s = (char*) data;
    printf("%s", s);
}

static void test_vector_int()
{
    q_vector v;
    q_vector_init(&v, 2);

    q_vector_add(&v, Q_INT_TO_VOIDPTR(10));
    q_vector_add(&v, Q_INT_TO_VOIDPTR(20));
    q_vector_add(&v, Q_INT_TO_VOIDPTR(30));
    q_vector_add(&v, Q_INT_TO_VOIDPTR(40));
    q_vector_add(&v, Q_INT_TO_VOIDPTR(50));

    for (size_t i = 0; i < v.len; ++i) {
        int s = Q_VOIDPTR_TO_INT(v.elems[i]);
        printf("%d\n", s);
    }
}

static void test_vector_str()
{
    q_vector v;
    q_vector_init(&v, 2);

    q_vector_add(&v, "aa");
    q_vector_add(&v, "bb");
    q_vector_add(&v, "cc");
    q_vector_add(&v, "dd");

    for (size_t i = 0; i < v.len; ++i) {
        char *s = v.elems[i];
        printf("%s\n", s);
    }
}

static void test_graph_print()
{
    q_graph g;
    q_graph_init(&g, 5, false, false);

    q_graph_add_edge(&g, 1, 2, 0);
    q_graph_add_edge(&g, 1, 3, 0);
    q_graph_add_edge(&g, 2, 4, 0);
    
    q_graph_print(&g);
}


int main(int argc, char** argv)
{
    test_vector_int();
    test_vector_str();
    test_graph_print();
    return (EXIT_SUCCESS);
}