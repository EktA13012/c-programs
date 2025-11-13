#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int W, int wt[], int val[], int n) {
    if (n == 0 || W == 0)
        return 0;
    
    if (wt[n - 1] > W)
        return knapsack(W, wt, val, n - 1);
    else
        return max(val[n - 1] + knapsack(W - wt[n - 1], wt, val, n - 1),
                   knapsack(W, wt, val, n - 1));
}

void findSelectedItems(int W, int wt[], int val[], int n) {
    int selected[n], count = 0, tempW = W;
    
    for (int i = n - 1; i >= 0; i--) {
        int withItem = (wt[i] <= tempW) ? 
                       val[i] + knapsack(tempW - wt[i], wt, val, i) : 0;
        int withoutItem = knapsack(tempW, wt, val, i);
        
        if (wt[i] <= tempW && withItem > withoutItem) {
            selected[count++] = i;
            tempW -= wt[i];
        }
    }
    
    printf("\nSelected Items: ");
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", selected[i] + 1);
    printf("(Total Weight: %d, Total Value: %d)\n", W - tempW, 
           knapsack(W, wt, val, n));
}

int main() {
    int n, W;
    
    printf("0-1 Knapsack Problem\n");
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    int val[n], wt[n];
    
    for (int i = 0; i < n; i++) {
        printf("Item %d - Weight: ", i + 1);
        scanf("%d", &wt[i]);
        printf("         Value: ", i + 1);
        scanf("%d", &val[i]);
    }
    
    printf("Knapsack capacity: ");
    scanf("%d", &W);
    
    printf("\nItem  Weight  Value\n");
    printf("---------------------\n");
    for (int i = 0; i < n; i++)
        printf("%-6d%-8d%-6d\n", i + 1, wt[i], val[i]);
    
    int maxValue = knapsack(W, wt, val, n);
    findSelectedItems(W, wt, val, n);
    
    printf("Maximum Value: %d\n", maxValue);
    
    return 0;
}