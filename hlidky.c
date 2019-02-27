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

int bts(edge **graph, int n, int max) {

}

int main() {
    int n, k, a, b, h, q, s, c;
    edge **graph;

    scanf("%d%d", &n, &k);
    graph = calloc(n, sizeof(edge*));
    initGraph(graph, k);
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
