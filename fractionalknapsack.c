#include <stdio.h>

struct Item {
    int weight;
    int value;
    int index;
    float ratio;
};

void swap(struct Item *a, struct Item *b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

// Sort items by value/weight ratio in descending order
void sortByRatio(struct Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].ratio < items[j + 1].ratio) {
                swap(&items[j], &items[j + 1]);
            }
        }
    }
}

float fractionalKnapsack(struct Item items[], int n, int capacity) {
    // Calculate value/weight ratio for each item
    for (int i = 0; i < n; i++) {
        items[i].ratio = (float)items[i].value / items[i].weight;
    }
    
    // Sort items by ratio
    sortByRatio(items, n);
    
    float totalValue = 0.0;
    int remainingCapacity = capacity;
    
    printf("\nItem  Weight  Value   Ratio   Taken\n");
    printf("---------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        if (remainingCapacity >= items[i].weight) {
            // Take full item
            totalValue += items[i].value;
            remainingCapacity -= items[i].weight;
            printf("%-6d%-8d%-8d%-8.2f%-8s\n", items[i].index, 
                   items[i].weight, items[i].value, items[i].ratio, "Full");
        } else if (remainingCapacity > 0) {
            // Take fraction of item
            float fraction = (float)remainingCapacity / items[i].weight;
            totalValue += items[i].value * fraction;
            printf("%-6d%-8d%-8d%-8.2f%.2f\n", items[i].index, 
                   items[i].weight, items[i].value, items[i].ratio, fraction);
            remainingCapacity = 0;
        } else {
            printf("%-6d%-8d%-8d%-8.2f%-8s\n", items[i].index, 
                   items[i].weight, items[i].value, items[i].ratio, "None");
        }
    }
    
    return totalValue;
}

int main() {
    int n, capacity;
    
    printf("Fractional Knapsack Problem\n");
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    struct Item items[n];
    
    for (int i = 0; i < n; i++) {
        items[i].index = i + 1;
        printf("Item %d - Weight: ", i + 1);
        scanf("%d", &items[i].weight);
        printf("         Value: ");
        scanf("%d", &items[i].value);
    }
    
    printf("Knapsack capacity: ");
    scanf("%d", &capacity);
    
    printf("\nOriginal Items:\n");
    printf("Item  Weight  Value\n");
    printf("--------------------\n");
    for (int i = 0; i < n; i++)
        printf("%-6d%-8d%-6d\n", items[i].index, items[i].weight, items[i].value);
    
    float maxValue = fractionalKnapsack(items, n, capacity);
    
    printf("\nMaximum Value: %.2f\n", maxValue);
    
    return 0;
}