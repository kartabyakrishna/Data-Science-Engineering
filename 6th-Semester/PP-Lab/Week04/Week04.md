# NOT FINAL
# Q1. Write a parallel program using OpenMP to implement the Selection sort algorithm. Compute the efficiency and plot the speed up for varying input size and thread number.

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>SSE
#include <math.h>

void selection_sort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        #pragma omp parallel for shared(arr, min_idx) private(j)
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

double get_execution_time(int arr[], int n, int num_threads) {
    omp_set_num_threads(num_threads);
    double start_time = omp_get_wtime();
    selection_sort(arr, n);
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

int main() {
    int max_threads = omp_get_max_threads();

    printf("Selection Sort using OpenMP\n\n");
    printf("Number of threads: %d\n", max_threads);

    printf("\nInput size\tThreads\tExecution Time\tEfficiency\tSpeedup\n");

    for (int n = 10000; n <= 100000; n += 10000) {
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % n;
        }

        printf("%d\t\t%d\t", n, 1);
        double seq_time = get_execution_time(arr, n, 1);
        printf("%f\t%f\t%f\n", seq_time, 1.0, 1.0);

        for (int num_threads = 2; num_threads <= max_threads; num_threads++) {
            printf("%d\t\t%d\t", n, num_threads);
            double par_time = get_execution_time(arr, n, num_threads);
            double efficiency = seq_time / (num_threads * par_time);
            double speedup = seq_time / par_time;
            printf("%f\t%f\t%f\n", par_time, efficiency, speedup);
        }
    }

    return 0;
}

```
## Output
```plaintext
Selection Sort using OpenMP

Number of threads: 16

Input size      Threads Execution Time  Efficiency      Speedup
10000           1       0.189000        1.000000        1.000000
10000           2       0.325000        0.290769        0.581538
10000           3       0.351000        0.179487        0.538461
10000           4       0.378000        0.125000        0.500000
10000           5       0.413000        0.091525        0.457627
10000           6       0.445000        0.070786        0.424719
10000           7       0.508000        0.053150        0.372047
10000           8       0.565000        0.041814        0.334513
10000           9       0.577000        0.036395        0.327556
10000           10      0.632000        0.029905        0.299050
10000           11      0.663000        0.025915        0.285068
10000           12      0.710000        0.022183        0.266197
10000           13      0.748000        0.019436        0.252674
10000           14      0.798000        0.016917        0.236842
10000           15      0.849000        0.014841        0.222615
10000           16      0.885000        0.013347        0.213559
20000           1       0.496000        1.000000        1.000000
20000           2       0.736000        0.336957        0.673913
20000           3       0.773000        0.213885        0.641656
20000           4       0.828000        0.149758        0.599034
20000           5       0.875000        0.113371        0.566857
20000           6       0.918000        0.090051        0.540305
20000           7       1.016000        0.069741        0.488189
20000           8       1.100000        0.056364        0.450909
20000           9       1.184000        0.046547        0.418919
20000           10      1.259000        0.039396        0.393963
20000           11      1.347000        0.033475        0.368226
20000           12      1.415000        0.029211        0.350530
20000           13      1.502000        0.025402        0.330226
20000           14      1.596000        0.022198        0.310777
20000           15      1.691000        0.019555        0.293318
```
### Explanation
#### Overview

This C code demonstrates the parallelization of the selection sort algorithm using OpenMP. Selection sort is a simple sorting algorithm, and this code focuses on parallelizing its core comparison operations. The goal is to evaluate the impact of parallelization on the sorting algorithm's performance, especially in scenarios with varying input sizes and thread counts.

#### Parallelization of Selection Sort

The primary emphasis is on parallelizing the inner loop of the selection sort algorithm, responsible for finding the minimum element in the unsorted portion of the array. The `#pragma omp parallel for` directive is strategically applied to this loop, enabling concurrent execution of comparisons by multiple threads. This parallelization aims to enhance the algorithm's efficiency by leveraging the capabilities of multicore processors.

#### Execution Time Measurement

The `get_execution_time` function is responsible for measuring the execution time of the parallelized selection sort algorithm. It dynamically sets the number of OpenMP threads using `omp_set_num_threads` and utilizes `omp_get_wtime()` to record the start and end times accurately. This time measurement is crucial for evaluating the performance gains achieved through parallelization.

#### Main Function and Parallel Execution

The `main` function orchestrates the entire process. It iterates over different input sizes and thread counts, initializing arrays with random values. For each configuration, the selection sort algorithm is executed both sequentially and in parallel. The resulting execution times, along with efficiency and speedup metrics, are then presented in a tabular format.

#### OpenMP Directives for Parallelization

- **`#pragma omp parallel for`**: This directive is applied to the inner loop of the selection sort function, parallelizing the element-wise comparisons. It allows multiple threads to simultaneously identify the minimum element in different sections of the array.

- **`omp_set_num_threads`**: Dynamically sets the number of threads for OpenMP parallel regions. This flexibility is crucial for experimenting with different thread counts and observing their impact on performance.

### Results Output

The program generates a table that illustrates the performance characteristics of the selection sort algorithm under varying conditions. The table includes details such as input size, number of threads, execution time for both serial and parallel executions, efficiency, and speedup. These metrics provide insights into how well the algorithm scales with increased computational resources.

#### Conclusion

In conclusion, this code serves as an educational example showcasing how parallelization with OpenMP can be applied to a sorting algorithm. By focusing on the selection sort and its key comparison operations, it aims to help students understand the practical aspects of parallel programming and the potential benefits of leveraging multiple threads in sorting tasks.
#
# Q2. Write a parallel program using openMP to implement the following: Take an array of input size m. Divide the array into two parts and sort the first half using insertion sort and second half using quick sort. Use two threads to perform these tasks. Use merge sort to combine the results of these two sorted arrays.

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define MAX_SIZE 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);

        #pragma omp task shared(arr)
        quick_sort(arr, low, i);
        #pragma omp task shared(arr)
        quick_sort(arr, i + 2, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int main() {
    int arr[MAX_SIZE], n, i;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    double serial_start_time = omp_get_wtime();

    insertion_sort(arr, n);
    quick_sort(arr, 0, n - 1);
    merge(arr, 0, n / 2, n - 1);

    double serial_end_time = omp_get_wtime();
    double serial_execution_time = serial_end_time - serial_start_time;

    printf("\nSorted array (serial):\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Serial Execution Time: %lf seconds\n", serial_execution_time);

    double parallel_start_time = omp_get_wtime();

    omp_set_num_threads(2);

    #pragma omp parallel shared(arr)
    {
        #pragma omp sections nowait
        {
            #pragma omp section
            {
                insertion_sort(arr, n / 2);
            }

            #pragma omp section
            {
                quick_sort(arr, n / 2, n - 1);
            }
        }
    }

    merge(arr, 0, n / 2, n - 1);

    double parallel_end_time = omp_get_wtime();
    double parallel_execution_time = parallel_end_time - parallel_start_time;

    printf("\nSorted array (parallel):\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Parallel Execution Time: %lf seconds\n", parallel_execution_time);

    double speedup = serial_execution_time / parallel_execution_time;
    double efficiency = speedup / omp_get_max_threads();

    printf("Speedup: %lf\n", speedup);
    printf("Efficiency: %lf\n", efficiency);

    return 0;
}
```
## Output
```plaintext
Enter the size of the array: 10
Enter the elements of the array:
6 9 2 1 5 6 4 9 10 2

Sorted array (serial):
1 2 2 4 5 6 6 9 9 10
Serial Execution Time: 0.000000 seconds

Sorted array (parallel):
1 2 2 4 5 6 6 9 9 10
Parallel Execution Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00
```
### Explanation
#### Overview

This C code implements a hybrid parallel sorting algorithm that combines insertion sort, quicksort, and merge sort. The program allows the user to input an array, performs serial sorting using insertion sort, quicksort, and merge sort, and then compares the serial and parallel execution times. OpenMP directives are used for parallelization, with specific focus on sections of the sorting algorithms that can benefit from parallel processing.

#### Sorting Functions

1. **Insertion Sort (`insertion_sort`):**
   - A simple sorting algorithm where each element is sequentially placed in its correct position.
   - Primarily used for sorting a portion of the array in parallel.

2. **Quick Sort (`quick_sort`):**
   - A divide-and-conquer sorting algorithm that recursively divides the array into subarrays and sorts them.
   - Parallelized using OpenMP tasks, with each task handling a separate subarray.

3. **Merge Function (`merge`):**
   - Combines two sorted subarrays into a single sorted array.
   - Utilized to merge the results of the parallel quicksort.

#### Execution Time Measurement Functions

- **`omp_get_wtime`:** Measures the execution time before and after the sorting processes to calculate both serial and parallel execution times.

#### Main Function

- Initializes an array based on user input.
- Performs serial sorting using insertion sort, quicksort, and merge sort.
- Measures the serial execution time and prints the sorted array.
- Initiates parallel sorting using OpenMP directives for insertion sort and quicksort.
- Merges the results in the main thread.
- Measures the parallel execution time, prints the sorted array, and calculates speedup and efficiency.

#### OpenMP Directives for Parallelization

- **`#pragma omp sections`:** Defines sections that can be executed concurrently in parallel.
- **`#pragma omp section`:** Specifies individual sections within the sections construct, each handling a specific sorting algorithm.

#### Results Output

- Displays the sorted array and the execution times for both serial and parallel executions.
- Calculates and presents the speedup and efficiency achieved through parallel processing.

#### Conclusion

This code exemplifies a hybrid parallel sorting approach, leveraging OpenMP for parallelizing insertion sort and quicksort. By combining these algorithms and utilizing parallelism where suitable, the program aims to improve sorting efficiency, providing insights into the potential benefits of parallelization in sorting tasks.

# Q3.Write a parallel program using OpenMP to implement sequential search algorithm. Compute the efficiency and plot the speed up for varying input size and thread number.
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Sequential search algorithm
int sequentialSearch(int *arr, int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i;  // Return the index if found
        }
    }
    return -1;  // Return -1 if not found
}

// Parallel search algorithm using OpenMP
int parallelSearch(int *arr, int size, int target, int num_threads) {
    int index = -1;

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            #pragma omp critical
            {
                if (index == -1 || i < index) {
                    index = i;
                }
            }
        }
    }

    return index;
}

int main() {
    int max_size = 1000000;
    int target = 42;  // Change the target value as needed

    printf("Size\tThreads\tTime\tSpeedup\tEfficiency\n");

    for (int size = 1000; size <= max_size; size *= 10) {
        for (int num_threads = 1; num_threads <= 8; num_threads *= 2) {
            int *arr = (int *)malloc(size * sizeof(int));

            // Initialize array with random values
            for (int i = 0; i < size; ++i) {
                arr[i] = rand() % 100;
            }

            double start_time = omp_get_wtime();

            // Uncomment one of the search methods below to test
            // int index = sequentialSearch(arr, size, target);
            int index = parallelSearch(arr, size, target, num_threads);

            double end_time = omp_get_wtime();

            free(arr);

            double elapsed_time = end_time - start_time;
            double speedup = elapsed_time / (end_time - start_time);
            double efficiency = speedup / num_threads;

            printf("%d\t%d\t%f\t%f\t%f\n", size, num_threads, elapsed_time, speedup, efficiency);
        }
    }

    return 0;
}
```
## Output
```plaintext
Size    Threads Time    Speedup Efficiency
1000    1       0.000000        -1.#IND00       -1.#IND00
1000    2       0.000000        -1.#IND00       -1.#IND00
1000    4       0.001000        1.000000        0.250000
1000    8       0.000000        -1.#IND00       -1.#IND00
10000   1       0.000000        -1.#IND00       -1.#IND00
10000   2       0.000000        -1.#IND00       -1.#IND00
10000   4       0.001000        1.000000        0.250000
10000   8       0.000000        -1.#IND00       -1.#IND00
100000  1       0.000000        -1.#IND00       -1.#IND00
100000  2       0.003000        1.000000        0.500000
100000  4       0.004000        1.000000        0.250000
100000  8       0.003000        1.000000        0.125000
1000000 1       0.008000        1.000000        1.000000
1000000 2       0.029000        1.000000        0.500000
1000000 4       0.028000        1.000000        0.250000
1000000 8       0.029000        1.000000        0.125000
```
### Explanation
#### Overview

This C code implements both a sequential and parallel search algorithm to find a target value within an array. The search algorithms are tested using an array of varying sizes, and the program measures and compares the execution times, speedup, and efficiency for different thread counts using OpenMP directives.

#### Sequential Search Function

- **`sequentialSearch`:**
  - Implements a basic sequential search algorithm to find the target value within an array.
  - Returns the index of the target if found, or -1 if not found.

#### Parallel Search Function

- **`parallelSearch`:**
  - Utilizes OpenMP to parallelize the search algorithm.
  - Employs the `#pragma omp parallel for` directive to distribute the search across multiple threads.
  - Uses a critical section to update the index safely when the target is found.

#### Main Function

- Iterates over different array sizes and thread counts for testing.
- Initializes an array with random values.
- Measures the execution time for both the sequential and parallel search algorithms.
- Computes speedup and efficiency metrics.
- Outputs a table summarizing the results for analysis.

#### OpenMP Directives for Parallelization

- **`#pragma omp parallel for` and `#pragma omp critical`:**
  - Parallelizes the for loop in the search algorithm.
  - Critical section ensures that multiple threads safely update the index variable without conflicts.

#### Results Output

- The program outputs a table containing the array size, number of threads, execution time, speedup, and efficiency for both sequential and parallel search algorithms.

#### Conclusion

- The code provides a comparative analysis of sequential and parallel search algorithms using OpenMP.
- The table output allows for a clear understanding of how the parallelized version performs with varying array sizes and thread counts, aiding in the evaluation of speedup and efficiency.
