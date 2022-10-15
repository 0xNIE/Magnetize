#include <stdlib.h>
#include <stdio.h>
#include "lab3.h"

/* evidence_graph: test graph */
void evidence_graph()
{
    printf("*** testing graph\n");
    graph(2, 0, 0, 1.8, -10, 10, -2, 25);
    graph(0.1, 0, 2, 1, -20, 20, -1, 20);
    graph(1, 2, -2, 0.5, -40, 40, -10, 40);
    graph(0, 0, 2, 2, -10, 10, 10, -10);
    graph(1, 0, 0, 0.5, -3, 4, -1, 16);
    graph (0, 2, 0, 1.33, -10, 10, -10, 20);
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_graph();

    return 0;
}
