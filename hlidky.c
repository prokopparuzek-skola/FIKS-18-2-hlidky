#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int to;
    int watchCount;
} edge;

void addEdge(edge *vertex, int to, int count) {
   while (vertex->to != -1) vertex++;
   vertex->to = to;
   vertex->watchCount = count;
}

void initGraph(edge **graph, int k) {
    int i, j;

    for (i = 0; i < k; i++) {
        for (j = 0; j < (k - 1) ; j++) {
            graph[i][j].to = -1;
            graph[i][j].watchCount = -1;
        }
    }
}

int main() {
    int n, k, a, b, h;
    edge **graph;

    scanf("%d%d", &n, &k);
    graph = calloc(n, sizeof(edge*));
    initGraph(graph, k);
    for (; k > 0; k--) {
        scanf("%d%d%d", &a, &b, &h);
        addEdge(graph[a], b, h);
    }

    // bacha prvně uvolni vrcholy pak až graf jako celek
    free(graph);
    return 0;
}
