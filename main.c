#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qsa/qsa_list.h"
#include "qsa/qsa_utils.h"

#include "qsa/graphs/qsa_graph.h"
#include "qsa/str/qsa_str.h"

#include "qsa/qsa_queue.h"
#include "qsa/qsa_stack.h"

#include "qsa/qsa_heap.h"

#include "qsa/qsa_dict.h"

#include "qsa/qsa_avl.h"

static void print_s(void *data) {
  char *s = (char *)data;
  printf("%s", s);
}

static void test_vector_int() {
  printf("\ntest vector int");

  struct qsa_vector *v = qsa_vector_create(2, sizeof(int));
  for (int i = 10; i <= 50; i += 10) {
    qsa_vector_add(v, &i);
  }

  for (size_t i = 0; i < v->len; ++i) {
    int s = QSA_VPTR_TO_INT(v->elems[i]);
    printf("%d\n", s);
  }

  qsa_vector_free(v);
}

static void test_vector_str() {
  printf("\ntest vector str");

  struct qsa_vector *v = qsa_vector_create(2, sizeof(char *));

  qsa_vector_add(v, "aa");
  qsa_vector_add(v, "bb");
  qsa_vector_add(v, "cc");
  qsa_vector_add(v, "dd");

  for (size_t i = 0; i < v->len; ++i) {
    char *s = v->elems[i];
    printf("%s\n", s);
  }

  qsa_vector_free(v);
}

static void test_queue() {
  printf("\ntest queue:\n");

  struct qsa_queue *q = qsa_queue_create_int();

  for (int i = 10; i <= 30; i += 10) {
    qsa_queue_enq(q, &i);
  }

  while (!qsa_queue_empty(q)) {
    printf("%d ", QSA_VPTR_TO_INT(qsa_queue_deq(q)));
  }

  qsa_queue_free(q);
}

static void test_stack() {
  printf("\ntest stack:\n");

  struct qsa_stack *s = qsa_stack_create(sizeof(int));

  for (int i = 10; i < 30; i += 10) {
    qsa_stack_push(s, &i);
  }

  while (!qsa_stack_empty(s)) {
    printf("%d ", QSA_VPTR_TO_INT(qsa_stack_pop(s)));
  }

  qsa_stack_free(s);
}

static void test_graph_print() {
  printf("\ntest graph printf");

  struct qsa_graph *g = qsa_graph_create(5, false, false);

  qsa_graph_add_edge(g, 1, 2, 0);
  qsa_graph_add_edge(g, 1, 3, 0);
  qsa_graph_add_edge(g, 2, 4, 0);

  qsa_graph_print(g);

  qsa_graph_free(g);
}

static void q_visit(struct qsa_graph *g, struct qsa_graph_edge *e, void *arg) {
  printf("%d ", e->b);
}

static struct qsa_graph *test_make_graph() {
  struct qsa_graph *g = qsa_graph_create(6, false, false);

  qsa_graph_add_edge(g, 1, 2, 0);
  qsa_graph_add_edge(g, 1, 3, 0);
  qsa_graph_add_edge(g, 1, 4, 0);
  qsa_graph_add_edge(g, 3, 5, 0);

  return g;
}

static void test_graph_bfs() {
  printf("\ntest graph bfs: ");

  struct qsa_graph *g = test_make_graph();

  qsa_graph_traversal_bfs(g, 1, q_visit, NULL);

  qsa_graph_free(g);
}

static void test_graph_dfs() {
  printf("\ntest graph dfs: ");

  struct qsa_graph *g = test_make_graph();

  qsa_graph_traversal_dfs(g, 1, q_visit, NULL);

  qsa_graph_free(g);
}

static void test_graph_paths() {
  printf("\ntest graph paths bfs: ");

  struct qsa_graph *g = test_make_graph();

  int s = 1;
  struct qsa_graph_paths *paths = qsa_graph_paths_new(g, s);
  qsa_graph_paths_bfs(g, paths);

  for (int i = 0; i < g->nv; ++i) {
    printf("\ndistance from %d to %d = %d", s, i, paths->dist[i]);
  }

  qsa_graph_paths_free(paths);
  qsa_graph_free(g);
}

static void test_heap() {
  struct qsa_heap *heap = qsa_heap_create(10, sizeof(int), &qsa_cmp_int);

  int x = 10;
  qsa_heap_add(heap, &x);

  printf("%d -> ", QSA_VPTR_TO_INT(qsa_heap_top(heap)));

  x = 20;
  qsa_heap_add(heap, &x);
  printf("%d -> ", QSA_VPTR_TO_INT(qsa_heap_top(heap)));

  x = 5;
  qsa_heap_add(heap, &x);
  printf("%d -> ", QSA_VPTR_TO_INT(qsa_heap_top(heap)));

  x = 30;
  qsa_heap_add(heap, &x);
  printf("%d -> ", QSA_VPTR_TO_INT(qsa_heap_top(heap)));

  x = 40;
  qsa_heap_add(heap, &x);
  printf("%d -> ", QSA_VPTR_TO_INT(qsa_heap_top(heap)));

  x = 2;
  qsa_heap_add(heap, &x);
  printf("%d -> ", QSA_VPTR_TO_INT(qsa_heap_top(heap)));

  printf("\n");

  int y1 = QSA_VPTR_TO_INT(qsa_heap_top(heap));
  printf("%d -> ", y1);
  qsa_heap_pop(heap);

  int y2 = QSA_VPTR_TO_INT(qsa_heap_top(heap));
  printf("%d -> ", y2);
  qsa_heap_pop(heap);

  int y3 = QSA_VPTR_TO_INT(qsa_heap_top(heap));
  printf("%d -> ", y3);
  qsa_heap_pop(heap);

  int y4 = QSA_VPTR_TO_INT(qsa_heap_top(heap));
  printf("%d -> ", y4);
  qsa_heap_pop(heap);

  int y5 = QSA_VPTR_TO_INT(qsa_heap_top(heap));
  printf("%d -> ", y5);
  qsa_heap_pop(heap);

  int y6 = QSA_VPTR_TO_INT(qsa_heap_top(heap));
  printf("%d -> ", y6);
  qsa_heap_pop(heap);

  int tmp = y3;
}

static void test_dict() {
  struct qsa_dict *d = qsa_dict_create(sizeof(char *), &qsa_hash_str,
                                       &qsa_same_int, sizeof(int));

  int x = 10;
  qsa_dict_add(d, "abc", &x);

  int y = 20;
  qsa_dict_add(d, "abcd", &y);

  int val1 = QSA_VPTR_TO_INT(qsa_dict_get(d, "abcd"));
  int val2 = QSA_VPTR_TO_INT(qsa_dict_get(d, "abc"));
}

static void print_int(void *data) { printf(" (%d) ", QSA_VPTR_TO_INT(data)); }

static void test_avl() {
  struct qsa_avl *t = qsa_avl_create(sizeof(int), &qsa_cmp_int);

  for (int i = 1; i <= 8; ++i) {
    qsa_avl_insert(t, &i);
  }

  qsa_avl_print(t, &print_int);

  qsa_avl_free(t);
}

enum sort_types { ST_INSERTION, ST_BUBBLE_SORT };

int main(int argc, char **argv) {
  test_dict();
  test_graph_bfs();
  test_graph_dfs();
  test_queue();
  test_stack();
  test_vector_int();
  test_vector_str();
  test_graph_print();
  test_graph_paths();

  return (EXIT_SUCCESS);
}
