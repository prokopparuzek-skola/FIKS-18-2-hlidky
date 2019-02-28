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

void findRoute(edge ** graph, buffer_t *queue) {
   int position = queue->b;

   while (position != queue->a) {
       printf("%d ", position);
       position = queue->parents[position];
   }
   printf("\n");
}

int bts(edge **graph, int n, int a, int b) {
    int i;
    int back; // návratová hodnota solveStep
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
        back = makeSteps(graph, &queue, i);
        if (back == 1) {
            findRoute(graph, &queue);
            printf("%d\n", i);
        }
    }
}

int makeSteps(edge **graph, buffer_t *queue, int max) {
    unsigned int i, *swapS;
    int back; // návratová hodnota solveStep

    for (i = 0; i <= queue->indexAc; i++) {
        back = solveStep(graph, queue, i, max);
        if (back == 1) {
            return 1;
        }
    }
    swapS = queue->stackAc;
    queue->stackAc = queue->stackFu;
    queue->stackFu = swapS;
    queue->indexAc = queue->indexFu;
    queue->indexFu = -1;
    return 0;
}

int solveStep(edge **graph, buffer_t *queue, int index, int max) {
    int i;
    for (i = 0; graph[index][i].to != -1; i++) {
        if (graph[index][i].watchCount <= max || queue->parents[graph[index][i].to] == -1) {
            queue->indexFu++; // zvyš index příštích bodů o 1
            queue->stackFu[queue->indexFu] = graph[index][i].to; // ulož tam aktuální bod
            queue->parents[graph[index][i].to] = queue->stackAc[queue->indexAc];
            if (graph[index][i].to == queue->b) {
                return 1;
            }
        }
    }
    return 0;
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
        addEdge(graph[b], a, h);
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
