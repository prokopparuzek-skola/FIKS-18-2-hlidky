#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct {
    int to;
    int watchCount;
} edge;

typedef struct {
    int a;
    int b;
    int indexAc;
    int indexFu;
    unsigned *stackAc;
    unsigned *stackFu;
    int *parents;
} buffer_t;

int makeSteps(edge **graph, buffer_t *queue, int max);
int solveStep(edge **graph, buffer_t *queue, int index, int b);

void addEdge(edge *vertex, int to, int count) {
   while (vertex->to != -1) vertex++;
   vertex->to = to;
   vertex->watchCount = count;
}

void initGraph(edge **graph, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < (n - 1) ; j++) {
            graph[i][j].to = -1;
            graph[i][j].watchCount = -1;
        }
    }
}

int bts(edge **graph, int n, int a, int b) {
    int i;
    buffer_t queue = {a, b, 0, -1, NULL, NULL}; // indexFu je -1, před 1. použitím se zvětší

    queue.stackAc = malloc(n * sizeof(unsigned));
    queue.stackFu = malloc(n * sizeof(unsigned));
    if (queue.stackAc == NULL || queue.stackFu == NULL) {
        puts("Málo paměti");
        exit(1);
    }
    memset(queue.parents, -1, n);
    queue.stackAc[0] = b;

    for (i = 0;; i++) {
        makeSteps(graph, &queue, i);
    }
}

int makeSteps(edge **graph, buffer_t *queue, int max) {
    unsigned int i, *swapS;

    for (i = 0; i <= queue->indexAc; i++) {
        solveStep(graph, queue, i, max);
    }
    swapS = queue->stackAc;
    queue->stackAc = queue->stackFu;
    queue->stackFu = swapS;
    queue->indexAc = queue->indexFu;
    queue->indexFu = -1;
}

int solveStep(edge **graph, buffer_t *queue, int index, int max) {
    int i;
    for (i = 0; graph[index][i].to != -1; i++) {
        if (graph[index][i].watchCount <= max) {
            queue->indexFu++; // zvyš index příštích bodů o 1
            queue->stackFu[queue->indexFu] = graph[index][i].to; // ulož tam aktuální bod
            queue->parents[graph[index][i].to] = queue->stackAc[queue->indexAc] ;
        }
    }
}

int main() {
    int n, k, a, b, h, q, s, c;
    edge **graph;

    scanf("%d%d", &n, &k);
    graph = calloc(n, sizeof(edge*));
    initGraph(graph, n);
    for (; k > 0; k--) {
        scanf("%d%d%d", &a, &b, &h);
        addEdge(graph[a], b, h);
    }
    scanf("%d", &q);
    for (; q > 0; q--) {
        scanf("%d%d", &s, &c);
    }

    for (n--; n >= 0; n--) {
        free(graph[n]);
    }
    free(graph);
    return 0;
}
