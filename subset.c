#include <stdio.h>
#include <stdbool.h>

int solutionCount = 0;

void printSubset(int set[], int subset[], int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d", set[subset[i]]);
        if (i < size - 1)
            printf(", ");
    }
    printf(" }\n");
}

void findSubsets(int set[], int n, int target, int subset[], int subsetSize, 
                 int sum, int index) {
    // If current sum equals target, print the subset
    if (sum == target) {
        solutionCount++;
        printf("Solution %d: ", solutionCount);
        printSubset(set, subset, subsetSize);
        return;
    }
    
    // If sum exceeds target or no more elements, return
    if (sum > target || index >= n)
        return;
    
    // Include current element and recurse
    subset[subsetSize] = index;
    findSubsets(set, n, target, subset, subsetSize + 1, sum + set[index], 
                index + 1);
    
    // Exclude current element and recurse
    findSubsets(set, n, target, subset, subsetSize, sum, index + 1);
}

void subsetSum(int set[], int n, int target) {
    int subset[n];
    solutionCount = 0;
    
    printf("\nFinding subsets with sum = %d:\n", target);
    printf("--------------------------------\n");
    
    findSubsets(set, n, target, subset, 0, 0, 0);
    
    if (solutionCount == 0) {
        printf("No solution found! No subset has sum equal to %d.\n", target);
    } else {
        printf("--------------------------------\n");
        printf("Total solutions found: %d\n", solutionCount);
    }
}

int main() {
    int n, target;
    
    printf("Subset Sum Problem\n");
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int set[n];
    
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &set[i]);
    }
    
    printf("Enter target sum: ");
    scanf("%d", &target);
    
    printf("\nGiven Set: { ");
    for (int i = 0; i < n; i++) {
        printf("%d", set[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf(" }\n");
    printf("Target Sum: %d\n", target);
    
    subsetSum(set, n, target);
    
    return 0;
}