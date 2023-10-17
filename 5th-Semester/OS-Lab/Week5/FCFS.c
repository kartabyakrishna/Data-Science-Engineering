#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int time[], int priority[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swap(&time[j], &time[j + 1]);
                swap(&priority[j], &priority[j + 1]);
            }
        }
    }
}

void fcfs(int arr[], int time[], int priority[], int n) {
    bubbleSort(arr, time, priority, n);
    int i;
    int wait[n];
    int tottime = 0;
    int turn[n];
    memset(wait, 0, n * sizeof(int));
    memset(turn, 0, n * sizeof(int));

    for (i = 0; i < n; i++) {
        printf("Process with priority %d is executing\n", priority[i]);
        if (i == 0) {
            wait[i] = arr[i];
            tottime += time[i];
            turn[i] = time[i] - arr[i];
        } else {
            wait[i] = tottime - arr[i];
            tottime += time[i];
            turn[i] = tottime - arr[i];
        }
        printf("%d %d %d\n", wait[i], tottime, turn[i]);
    }

    float avgwait = 0.0, avgburst = 0.0;
    for (i = 0; i < n; i++) {
        avgburst += turn[i];
        avgwait += wait[i];
    }
    avgwait /= n;
    avgburst /= n;

    printf("Average Burst Time %f ", avgburst);
    printf("\nAverage Wait Time %f \n", avgwait);
}

int main() {
    int arr[100], time[100], priority[100], n, i;
    printf("Enter the number of processes\n");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Arrival Time for process P%d ", i);
        scanf("%d", &arr[i]);
        printf("Burst time for process P%d ", i);
        scanf("%d", &time[i]);
        printf("Priority for process P%d ", i);
        scanf("%d", &priority[i]);
    }

    fcfs(arr, time, priority, n);

    return 0;
}

