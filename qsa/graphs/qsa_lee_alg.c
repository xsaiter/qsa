#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "qsa_lee_alg.h"

#include "../qsa_queue.h"
#include "../qsa_vector.h"

#define QSA_DIRECTIONS (4)

bool qsa_lee_alg(qsa_lee_opts_s *opts, qsa_vector_s *result)
{
    int dx[QSA_DIRECTIONS] = {1, 0, -1, 0};
    int dy[QSA_DIRECTIONS] = {0, -1, 0, 1};

    qsa_queue_s *q = qsa_queue_create(sizeof(qsa_lee_cell_s));

    int bx = opts->beg_x;
    int by = opts->beg_y;

    int rows = opts->rows;
    int cols = opts->cols;

    qsa_lee_cell_s cc[rows][cols];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cc[i][j].visited = false;
            cc[i][j].n = 0;
        }
    }

    cc[bx][by].n = 1;
    cc[bx][by].x = bx;
    cc[bx][by].y = by;
    cc[bx][by].visited = true;

    qsa_queue_enq(q, &cc[bx][by]);

    int x, y, num, nx, ny;

    bool stop = false;

    while (!stop && !qsa_queue_empty(q)) {

        qsa_lee_cell_s *c = qsa_queue_deq(q);
        x = c->x;
        y = c->y;
        num = c->n + 1;

        for (int i = 0; i < QSA_DIRECTIONS; ++i) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && !cc[nx][ny].visited && opts->a[nx][ny] == 0) {
                cc[nx][ny].x = nx;
                cc[nx][ny].y = ny;
                cc[nx][ny].n = num;
                cc[nx][ny].visited = true;

                if (nx == opts->end_x && ny == opts->end_y) {
                    stop = true;
                    break;
                }

                qsa_queue_enq(q, &cc[nx][ny]);
            }
        }
    }

    qsa_queue_free(q);

    if (!stop) {
        return false;
    }

    x = opts->end_x;
    y = opts->end_y;
    num = cc[x][y].n;

    while (x != bx || y != by) {
        for (int i = 0; i < QSA_DIRECTIONS; ++i) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (cc[nx][ny].n == num - 1) {
                num = cc[nx][ny].n;

                qsa_lee_cell_s *cell = malloc(sizeof (qsa_lee_cell_s));

                memcpy(cell, &cc[nx][ny], sizeof (qsa_lee_cell_s));

                qsa_vector_add(result, cell);

                x = nx;
                y = ny;

                break;
            }
        }
    }

    return true;
}