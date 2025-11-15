#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int vertices, edges;
    struct Edge* edge;
};

struct Graph* createGraph(int vertices, int edges) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->edges = edges;
    graph->edge = (struct Edge*)malloc(edges * sizeof(struct Edge));
    return graph;
}

// Find set of an element (uses path compression)
int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

// Union of two sets (uses union by rank)
void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Compare function for sorting edges by weight
int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

void kruskalMST(struct Graph* graph) {
    int vertices = graph->vertices;
    struct Edge result[vertices];
    int e = 0;  // Index for result[]
    int i = 0;  // Index for sorted edges
    
    // Sort all edges in ascending order by weight
    qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compare);
    
    printf("\nSorted Edges by Weight:\n");
    printf("Edge      Weight\n");
    printf("----------------\n");
    for (int j = 0; j < graph->edges; j++) {
        printf("%d - %d   %d\n", graph->edge[j].src, graph->edge[j].dest, 
               graph->edge[j].weight);
    }
    
    int parent[vertices];
    int rank[vertices];
    
    // Initialize parent and rank
    for (int v = 0; v < vertices; v++) {
        parent[v] = v;
        rank[v] = 0;
    }
    
    printf("\nEdge Selection Process:\n");
    printf("Edge      Weight  Status\n");
    printf("---------------------------\n");
    
    // Pick smallest edge and check if it forms cycle
    while (e < vertices - 1 && i < graph->edges) {
        struct Edge nextEdge = graph->edge[i++];
        
        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);
        
        if (x != y) {
            result[e++] = nextEdge;
            unionSets(parent, rank, x, y);
            printf("%d - %d   %-7d Accepted\n", nextEdge.src, nextEdge.dest, 
                   nextEdge.weight);
        } else {
            printf("%d - %d   %-7d Rejected (forms cycle)\n", 
                   nextEdge.src, nextEdge.dest, nextEdge.weight);
        }
    }
    
    printf("\nMinimum Spanning Tree:\n");
    printf("Edge      Weight\n");
    printf("----------------\n");
    
    int totalCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d - %d   %d\n", result[i].src, result[i].dest, result[i].weight);
        totalCost += result[i].weight;
    }
    
    printf("----------------\n");
    printf("Total Cost: %d\n", totalCost);
}

int main() {
    int vertices, edges;
    
    printf("Kruskal's Algorithm - Minimum Spanning Tree\n");
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    struct Graph* graph = createGraph(vertices, edges);
    
    printf("\nEnter edges (vertex1 vertex2 weight):\n");
    for (int i = 0; i < edges; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, 
              &graph->edge[i].weight);
    }
    
    printf("\nInput Graph Edges:\n");
    printf("Edge      Weight\n");
    printf("----------------\n");
    for (int i = 0; i < edges; i++) {
        printf("%d - %d   %d\n", graph->edge[i].src, graph->edge[i].dest, 
               graph->edge[i].weight);
    }
    
    kruskalMST(graph);
    
    free(graph->edge);
    free(graph);
    
    return 0;
}