#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "q_lee_alg.h"

#include "../q_queue.h"
#include "../q_vector.h"

#define Q_DIRECTIONS (4)

bool q_lee_alg(q_lee_opts *opts, q_vector *result)
{
    int dx[Q_DIRECTIONS] = {1, 0, -1, 0};
    int dy[Q_DIRECTIONS] = {0, -1, 0, 1};

    q_queue q;

    int bx = opts->beg_x;
    int by = opts->beg_y;

    int rows = opts->rows;
    int cols = opts->cols;

    q_lee_cell cc[rows][cols];

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

    q_queue_enq(&q, &cc[bx][by]);

    int x, y, num, nx, ny;

    bool stop = false;

    while (!stop && !q_queue_empty(&q)) {

        q_lee_cell *c = q_queue_deq(&q);
        x = c->x;
        y = c->y;
        num = c->n + 1;

        for (int i = 0; i < Q_DIRECTIONS; ++i) {
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

                q_queue_enq(&q, &cc[nx][ny]);
            }
        }
    }

    q_queue_destroy(&q);

    if (!stop) {
        return false;
    }

    x = opts->end_x;
    y = opts->end_y;
    num = cc[x][y].n;

    while (x != bx || y != by) {
        for (int i = 0; i < Q_DIRECTIONS; ++i) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (cc[nx][ny].n == num - 1) {
                num = cc[nx][ny].n;

                q_lee_cell *cell = malloc(sizeof (q_lee_cell));

                memcpy(cell, &cc[nx][ny], sizeof (q_lee_cell));

                q_vector_add(result, cell);

                x = nx;
                y = ny;

                break;
            }
        }
    }

    return true;
}