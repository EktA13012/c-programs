#include <stdio.h>
#include <stdbool.h>

struct Task {
    int id;
    int deadline;
    int profit;
};

void swap(struct Task *a, struct Task *b) {
    struct Task temp = *a;
    *a = *b;
    *b = temp;
}

void sortByProfit(struct Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].profit < tasks[j + 1].profit) {
                swap(&tasks[j], &tasks[j + 1]);
            }
        }
    }
}

int findMaxDeadline(struct Task tasks[], int n) {
    int max = tasks[0].deadline;
    for (int i = 1; i < n; i++) {
        if (tasks[i].deadline > max)
            max = tasks[i].deadline;
    }
    return max;
}

void scheduleJobs(struct Task tasks[], int n) {
    sortByProfit(tasks, n);
    
    int maxDeadline = findMaxDeadline(tasks, n);
    int slot[maxDeadline];
    bool slotFilled[maxDeadline];
    
    for (int i = 0; i < maxDeadline; i++) {
        slotFilled[i] = false;
        slot[i] = -1;
    }
    
    int totalProfit = 0, jobCount = 0;
    
    printf("\nTask  Deadline  Profit  Slot\n");
    printf("-----------------------------\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = tasks[i].deadline - 1; j >= 0; j--) {
            if (!slotFilled[j]) {
                slotFilled[j] = true;
                slot[j] = i;
                totalProfit += tasks[i].profit;
                jobCount++;
                printf("%-6d%-10d%-8d%d\n", tasks[i].id, tasks[i].deadline, 
                       tasks[i].profit, j + 1);
                break;
            }
        }
    }
    
    printf("\nScheduled: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slotFilled[i])
            printf("T%d ", tasks[slot[i]].id);
    }
    printf("\nTotal Tasks: %d | Total Profit: %d\n", jobCount, totalProfit);
}

int main() {
    int n;
    
    printf("Task Scheduling Problem\n");
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    
    struct Task tasks[n];
    
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Task %d - Deadline: ", i + 1);
        scanf("%d", &tasks[i].deadline);
        printf("         Profit: ");
        scanf("%d", &tasks[i].profit);
    }
    
    printf("\nTask  Deadline  Profit\n");
    printf("----------------------\n");
    for (int i = 0; i < n; i++)
        printf("%-6d%-10d%-6d\n", tasks[i].id, tasks[i].deadline, tasks[i].profit);
    
    scheduleJobs(tasks, n);
    
    return 0;
}