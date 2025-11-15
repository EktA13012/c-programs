#include <stdio.h>
#include <limits.h>

#define INF 99999
#define MAX 100

void printMatrix(int dist[][MAX], int vertices) {
    printf("   ");
    for (int i = 0; i < vertices; i++)
        printf("%4d", i);
    printf("\n");
    
    for (int i = 0; i < vertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF)
                printf(" INF");
            else
                printf("%4d", dist[i][j]);
        }
        printf("\n");
    }
}

void printPath(int next[][MAX], int u, int v) {
    if (next[u][v] == -1) {
        printf("No path");
        return;
    }
    
    printf("%d", u);
    while (u != v) {
        u = next[u][v];
        printf(" -> %d", u);
    }
}

void floydWarshall(int graph[][MAX], int vertices) {
    int dist[MAX][MAX], next[MAX][MAX];
    
    // Initialize distance and next arrays
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }
    
    printf("\nInitial Distance Matrix:\n");
    printMatrix(dist, vertices);
    
    // Floyd-Warshall algorithm
    for (int k = 0; k < vertices; k++) {
        printf("\nAfter considering vertex %d as intermediate:\n", k);
        
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
        printMatrix(dist, vertices);
    }
    
    printf("\n\nShortest Paths:\n");
    printf("From -> To   Distance   Path\n");
    printf("------------------------------------\n");
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i != j) {
                printf("%4d -> %2d   ", i, j);
                if (dist[i][j] == INF)
                    printf("INF        No path\n");
                else {
                    printf("%-10d ", dist[i][j]);
                    printPath(next, i, j);
                    printf("\n");
                }
            }
        }
    }
}

int main() {
    int vertices, edges;
    int graph[MAX][MAX];
    
    printf("Floyd-Warshall Algorithm - All Pairs Shortest Paths\n");
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    // Initialize graph with INF
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("\nEnter edges (source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }
    
    printf("\nInput Graph (Adjacency Matrix):\n");
    printMatrix(graph, vertices);
    
    floydWarshall(graph, vertices);
    
    return 0;
}