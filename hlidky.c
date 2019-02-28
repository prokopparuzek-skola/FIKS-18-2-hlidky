#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define RESET_PAR for (j = 0; j < n; j++) queue.parents[j] = -1

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
        graph[i] = malloc(n * sizeof(edge));
        for (j = 0; j < (n - 1) ; j++) {
            graph[i][j].to = -1;
            graph[i][j].watchCount = -1;
        }
    }
}

void findRoute(edge ** graph, buffer_t *queue, int n) {
   int position = queue->b;
   int route[n];
   int *index = route;

   while (position != queue->a) {
       *index++ = position;
       position = queue->parents[position];
   }
   *index = queue->a;
   while (index != route) {
       printf("%d ", *index);
       index--;
   }
   printf("%d\n", *index);
}

int solve(edge **graph, buffer_t *queue, int max) {
    int back = 1;
    while (back == 1) {
        back = makeSteps(graph, queue, max);
    }
    return back;
}

void bts(edge **graph, int n, int a, int b, int maxCount) {
    int i, j;
    int back; // návratová hodnota solveStep
    buffer_t queue = {a, b, 0, -1, NULL, NULL, NULL}; // indexFu je -1, před 1. použitím se zvětší

    queue.stackAc = malloc(n * sizeof(unsigned));
    queue.stackFu = malloc(n * sizeof(unsigned));
    queue.parents = malloc(n * sizeof(int));
    if (queue.stackAc == NULL || queue.stackFu == NULL) {
        puts("Málo paměti");
        exit(1);
    }

    for (i = 0;; i++) {
        RESET_PAR;
        queue.stackAc[0] = a;
        queue.indexAc = 0;
        queue.indexFu = -1;
        queue.parents[a] = a;
        back = solve(graph, &queue, i);
        if (back == 0) {
            findRoute(graph, &queue, n);
            printf("%d\n", i);
            break;
        }
        if (i == maxCount && back == 2) {
            printf("1 2 3\n");
            printf("-1\n");
        }
    }
}

int makeSteps(edge **graph, buffer_t *queue, int max) {
    unsigned int i, *swapS, test = 0;
    int back; // návratová hodnota solveStep

    for (i = 0; i <= queue->indexAc; i++) {
        back = solveStep(graph, queue, i, max);
        if (back == 0) {
            return 0;
        }
        if (back != 2) {
            test = 1;
        }
    }
    if (test == 1) {
        swapS = queue->stackAc;
        queue->stackAc = queue->stackFu;
        queue->stackFu = swapS;
        queue->indexAc = queue->indexFu;
        queue->indexFu = -1;
        return 1;
    }
    return 2;
}

int solveStep(edge **graph, buffer_t *queue, int index, int max) {
    int i, test = 0;
    for (i = 0; graph[queue->stackAc[index]][i].to != -1; i++) {
        if (graph[queue->stackAc[index]][i].watchCount <= max && queue->parents[graph[queue->stackAc[index]][i].to] == -1) {
            test = 1;
            queue->indexFu++; // zvyš index příštích bodů o 1
            queue->stackFu[queue->indexFu] = graph[queue->stackAc[index]][i].to; // ulož tam aktuální bod
            queue->parents[graph[queue->stackAc[index]][i].to] = queue->stackAc[queue->indexAc];
            if (graph[queue->stackAc[index]][i].to == queue->b) {
                return 0;
            }
        }
    }
    return test?1:2;
}

int main() {
    int n, k, a, b, h, q, s, c;
    int maxCount = 0;
    edge **graph;

    scanf("%d%d", &n, &k);
    graph = calloc(n, sizeof(edge*));
    initGraph(graph, n);
    for (; k > 0; k--) {
        scanf("%d%d%d", &a, &b, &h);
        a--;
        b--;
        addEdge(graph[a], b, h);
        addEdge(graph[b], a, h);
        if (h > maxCount) {
            maxCount = h;
        }
    }
    scanf("%d", &q);
    for (; q > 0; q--) {
        scanf("%d%d", &s, &c);
        s--;
        c--;
        bts(graph, n, s, c,maxCount);
    }

    for (n--; n >= 0; n--) {
        free(graph[n]);
    }
    free(graph);
    return 0;
}
