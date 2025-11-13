#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

int minKey(int key[], bool mstSet[], int vertices) {
    int min = INT_MAX, minIndex;
    
    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printMST(int parent[], int graph[MAX][MAX], int vertices) {
    printf("\nMinimum Spanning Tree:\n");
    printf("Edge    Weight\n");
    printf("---------------\n");
    
    int totalCost = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d   %d\n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }
    
    printf("---------------\n");
    printf("Total Cost: %d\n", totalCost);
}

void primMST(int graph[MAX][MAX], int vertices) {
    int parent[vertices];  // Array to store MST
    int key[vertices];     // Key values to pick minimum weight edge
    bool mstSet[vertices]; // To track vertices included in MST
    
    // Initialize all keys as infinite
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    
    // Start with first vertex
    key[0] = 0;
    parent[0] = -1;
    
    printf("\nStep-by-step Process:\n");
    printf("Step  Vertex  Key  Parent\n");
    printf("---------------------------\n");
    
    for (int count = 0; count < vertices; count++) {
        // Pick minimum key vertex not yet in MST
        int u = minKey(key, mstSet, vertices);
        mstSet[u] = true;
        
        printf("%-6d%-8d%-5d%-7d\n", count + 1, u, key[u], 
               (parent[u] == -1) ? -1 : parent[u]);
        
        // Update key values of adjacent vertices
        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    printMST(parent, graph, vertices);
}

int main() {
    int vertices, edges;
    int graph[MAX][MAX] = {0};
    
    printf("Prim's Algorithm - Minimum Spanning Tree\n");
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("\nEnter edges (vertex1 vertex2 weight):\n");
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;  // Undirected graph
    }
    
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < vertices; i++)
        printf("%3d", i);
    printf("\n");
    
    for (int i = 0; i < vertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < vertices; j++) {
            if (graph[i][j] == 0)
                printf("  -");
            else
                printf("%3d", graph[i][j]);
        }
        printf("\n");
    }
    
    primMST(graph, vertices);
    
    return 0;
}