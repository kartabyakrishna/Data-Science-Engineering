#include <pthread.h>
#include <stdio.h>

#define MAX_SIZE 100

int nums[MAX_SIZE];
int evenSum = 0;
int oddSum = 0;

void* sumEven(void* arg) {
    int* arr = (int*)arg;
    int n = arr[0];

    for (int i = 1; i <= n; i++) {
        if (arr[i] % 2 == 0)	evenSum += arr[i];
    }
    return NULL;
}

void* sumOdd(void* arg) {
    int* arr = (int*)arg;
    int n = arr[0];

    for (int i = 1; i <= n; i++) {
        if (arr[i] % 2 != 0)	oddSum += arr[i];
    }
    return NULL;
}

int main() {
    int n;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter %d elements of the array:\n", n);
    nums[0] = n;

    for (int i = 1; i <= n; ++i)	scanf("%d", &nums[i]);

    pthread_t threadEven, threadOdd;

    pthread_create(&threadEven, NULL, sumEven, nums);
    pthread_create(&threadOdd, NULL, sumOdd, nums);

    pthread_join(threadEven, NULL);
    pthread_join(threadOdd, NULL);

    printf("Sum of the even numbers: %d\n", evenSum);
    printf("Sum of the odd numbers: %d\n", oddSum);

    return 49;
}
