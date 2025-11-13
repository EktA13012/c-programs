#include <stdio.h>
#include <limits.h>

// Recursive function to find minimum number of multiplications
int matrixChainOrderRecursive(int p[], int i, int j) {
    // Base case: only one matrix, no multiplication needed
    if (i == j)
        return 0;
    
    int min = INT_MAX;
    
    // Try all possible split points
    for (int k = i; k < j; k++) {
        // Cost of multiplying matrices from i to k, k+1 to j
        // plus cost of multiplying the two resulting matrices
        int count = matrixChainOrderRecursive(p, i, k) +
                    matrixChainOrderRecursive(p, k + 1, j) +
                    p[i - 1] * p[k] * p[j];
        
        if (count < min)
            min = count;
    }
    
    return min;
}

// Function to find optimal split point recursively
int findOptimalSplit(int p[], int i, int j, int minCost) {
    if (i == j)
        return -1;
    
    for (int k = i; k < j; k++) {
        int count = matrixChainOrderRecursive(p, i, k) +
                    matrixChainOrderRecursive(p, k + 1, j) +
                    p[i - 1] * p[k] * p[j];
        
        if (count == minCost)
            return k;
    }
    return -1;
}

// Function to print parenthesization
void printParenthesis(int p[], int i, int j, char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    
    int minCost = matrixChainOrderRecursive(p, i, j);
    int k = findOptimalSplit(p, i, j, minCost);
    
    printf("(");
    printParenthesis(p, i, k, name);
    printParenthesis(p, k + 1, j, name);
    printf(")");
}

// Function to calculate and display all sub-chain costs
void displayAllCosts(int p[], int n) {
    printf("\nCost Matrix (minimum cost for multiplying matrices i to j):\n");
    printf("     ");
    for (int i = 1; i < n; i++)
        printf("%7d ", i);
    printf("\n");
    
    for (int i = 1; i < n; i++) {
        printf("%2d | ", i);
        for (int j = 1; j < n; j++) {
            if (j < i)
                printf("      - ");
            else if (i == j)
                printf("      0 ");
            else
                printf("%7d ", matrixChainOrderRecursive(p, i, j));
        }
        printf("\n");
    }
}

int main() {
    int n;
    
    printf("Matrix Chain Multiplication\n");
    printf("============================\n\n");
    
    printf("Enter the number of matrices: ");
    scanf("%d", &n);
    
    int p[n + 1];
    
    printf("\nEnter the dimensions of matrices:\n");
    printf("(For %d matrices, enter %d values representing dimensions)\n", n, n + 1);
    printf("Matrix i has dimensions p[i-1] x p[i]\n\n");
    
    for (int i = 0; i <= n; i++) {
        printf("p[%d]: ", i);
        scanf("%d", &p[i]);
    }
    
    printf("\nMatrix dimensions:\n");
    for (int i = 1; i <= n; i++) {
        printf("Matrix %c: %d x %d\n", 'A' + i - 1, p[i - 1], p[i]);
    }
    
    int minCost = matrixChainOrderRecursive(p, 1, n);
    printf("\nOptimal Cost (Minimum scalar multiplications): %d\n", minCost);
    
    displayAllCosts(p, n + 1);
    
    printf("\nOptimal Parenthesization: ");
    char name = 'A';
    printParenthesis(p, 1, n, &name);
    printf("\n");
    
    
    printf("Time Complexity: O(2^n) - Exponential\n");
    
    
    return 0;
}