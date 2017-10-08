#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "q_list.h"
#include "q_utils.h"

#include "str/q_str.h"
#include "graphs/q_graph.h"

#include "q_queue.h"
#include "q_stack.h"

#include "q_heap.h"

#include "q_dict.h"

struct person {
    int age;
};

static void print_s(void *data)
{
    char* s = (char*) data;
    printf("%s", s);
}

static void test_vector_int()
{
    printf("\ntest vector int");

    q_vector *v = q_vector_new(2, sizeof (int));
    for (int i = 10; i <= 50; i += 10) {
        q_vector_add(v, &i);
    }

    for (size_t i = 0; i < v->len; ++i) {
        int s = Q_VPTR_TO_INT(v->elems[i]);
        printf("%d\n", s);
    }

    q_vector_free(v);
}

static void test_vector_str()
{
    printf("\ntest vector str");

    q_vector *v = q_vector_new(2, sizeof (char*));

    q_vector_add(v, "aa");
    q_vector_add(v, "bb");
    q_vector_add(v, "cc");
    q_vector_add(v, "dd");

    for (size_t i = 0; i < v->len; ++i) {
        char *s = v->elems[i];
        printf("%s\n", s);
    }

    q_vector_free(v);
}

static void test_queue()
{
    printf("\ntest queue:\n");

    q_queue *q = q_queue_new_int();

    for (int i = 10; i <= 30; i += 10) {
        q_queue_enq(q, &i);
    }

    while (!q_queue_empty(q)) {
        printf("%d ", Q_VPTR_TO_INT(q_queue_deq(q)));
    }

    q_queue_free(q);
}

static void test_stack()
{
    printf("\ntest stack:\n");

    q_stack *s = q_stack_new_int();

    for (int i = 10; i < 30; i += 10) {
        q_stack_push(s, &i);
    }

    while (!q_stack_empty(s)) {
        printf("%d ", Q_VPTR_TO_INT(q_stack_pop(s)));
    }

    q_stack_free(s);
}

static void test_graph_print()
{
    printf("\ntest graph printf");

    q_graph *g = q_graph_new(5, false, false);

    q_graph_add_edge(g, 1, 2, 0);
    q_graph_add_edge(g, 1, 3, 0);
    q_graph_add_edge(g, 2, 4, 0);

    q_graph_print(g);

    q_graph_free(g);
}

static void q_visit(q_graph *g, q_graph_edge *e, void *arg)
{
    printf("%d ", e->b);
}

static q_graph *test_make_graph()
{
    q_graph *g = q_graph_new(6, false, false);

    q_graph_add_edge(g, 1, 2, 0);
    q_graph_add_edge(g, 1, 3, 0);
    q_graph_add_edge(g, 1, 4, 0);
    q_graph_add_edge(g, 3, 5, 0);

    return g;
}

static void test_graph_bfs()
{
    printf("\ntest graph bfs: ");

    q_graph *g = test_make_graph();

    q_graph_traversal_bfs(g, 1, q_visit, NULL);

    q_graph_free(g);
}

static void test_graph_dfs()
{
    printf("\ntest graph dfs: ");

    q_graph *g = test_make_graph();

    q_graph_traversal_dfs(g, 1, q_visit, NULL);

    q_graph_free(g);
}

static void test_graph_paths()
{
    printf("\ntest graph paths bfs: ");

    q_graph *g = test_make_graph();

    int s = 1;
    q_graph_paths *paths = q_graph_paths_new(g, s);
    q_graph_paths_bfs(g, paths);

    for (int i = 0; i < g->nv; ++i) {
        printf("\ndistance from %d to %d = %d", s, i, paths->dist[i]);
    }

    q_graph_paths_free(paths);
    q_graph_free(g);
}

static void test_heap()
{
    q_heap *heap = q_heap_new(10, sizeof (int), &q_compare_int);

    int x = 10;
    q_heap_add(heap, &x);

    printf("%d -> ", Q_VPTR_TO_INT(q_heap_top(heap)));

    x = 20;
    q_heap_add(heap, &x);
    printf("%d -> ", Q_VPTR_TO_INT(q_heap_top(heap)));

    x = 5;
    q_heap_add(heap, &x);
    printf("%d -> ", Q_VPTR_TO_INT(q_heap_top(heap)));

    x = 30;
    q_heap_add(heap, &x);
    printf("%d -> ", Q_VPTR_TO_INT(q_heap_top(heap)));

    x = 40;
    q_heap_add(heap, &x);
    printf("%d -> ", Q_VPTR_TO_INT(q_heap_top(heap)));

    x = 2;
    q_heap_add(heap, &x);
    printf("%d -> ", Q_VPTR_TO_INT(q_heap_top(heap)));

    printf("\n");

    int y1 = Q_VPTR_TO_INT(q_heap_top(heap));
    printf("%d -> ", y1);
    q_heap_pop(heap);

    int y2 = Q_VPTR_TO_INT(q_heap_top(heap));
    printf("%d -> ", y2);
    q_heap_pop(heap);

    int y3 = Q_VPTR_TO_INT(q_heap_top(heap));
    printf("%d -> ", y3);
    q_heap_pop(heap);

    int y4 = Q_VPTR_TO_INT(q_heap_top(heap));
    printf("%d -> ", y4);
    q_heap_pop(heap);

    int y5 = Q_VPTR_TO_INT(q_heap_top(heap));
    printf("%d -> ", y5);
    q_heap_pop(heap);

    int y6 = Q_VPTR_TO_INT(q_heap_top(heap));
    printf("%d -> ", y6);
    q_heap_pop(heap);

    int tmp = y3;

}

static void test_dict()
{    
    q_dict *d = q_dict_new(sizeof(char*), &q_hash_str, &q_equals_int, sizeof(int));
 
    int x = 10;
    q_dict_add(d, "abc", &x);

    int y = 20;
    q_dict_add(d, "abcd", &y);

    int val1 = Q_VPTR_TO_INT(q_dict_get(d, "abcd"));
    int val2 = Q_VPTR_TO_INT(q_dict_get(d, "abc"));
}

int main(int argc, char** argv)
{
    test_dict();
    /*
    test_graph_bfs();
    test_graph_dfs();
    test_queue();
    test_stack();
    test_vector_int();
    test_vector_str();
    test_graph_print();
    test_graph_paths();
    
    test_priority_queue();
     */
    return (EXIT_SUCCESS);
}