#include <stdio.h>
#include "stdlib.h"
#define BLOCK 16

typedef struct {
    int to;
    int watchCount;
} edge;

int main() {
    int n, k, a, b, h;
    edge **graph;

    scanf("%d%d", &n, &k);
    graph =calloc(n, sizeof(edge*));
    for (; k > 0; k--) {
        scanf("%d%d%d", &a, &b, &h);
    }

    // bacha prvně uvolni vrcholy pak až graf jako celek
    free(graph);
    return 0;
}
