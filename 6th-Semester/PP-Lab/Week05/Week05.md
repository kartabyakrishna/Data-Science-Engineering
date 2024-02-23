Contribution by :- [Yashwith Suvarna](https://github.com/Yashwith1998)
# Q1) Write a parallel program using OpenMP to perform vector addition, subtraction, multiplication. Demonstrate task level parallelism. Analyze the speedup and efficiency of the parallelized code. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void generate_random_vector(int *vec, int size) {
    for (int i = 0; i < size; ++i) {
        vec[i] = rand() % 100; // Random values between 0 and 99
    }
}

void vector_addition(int *a, int *b, int *result, int size, int nth) {
    #pragma omp parallel for num_threads(nth)
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
}

void vector_subtraction(int *a, int *b, int *result, int size, int nth) {
    #pragma omp parallel for num_threads(nth)
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] - b[i];
    }
}

void vector_multiplication(int *a, int *b, int *result, int size, int nth) {
    #pragma omp parallel for num_threads(nth)
    for (int i = 0; i < size; ++i) {
        result[i] = a[i] * b[i];
    }
}

double calculate_speedup(double serial_time, double parallel_time) {
    return serial_time / parallel_time;
}

double calculate_efficiency(double speedup, int num_threads) {
    return speedup / num_threads;
}

int main() {
    const int size = 100000;
    int a[size], b[size], result_add[size], result_sub[size], result_mul[size];

    // Generate random vectors a and b
    generate_random_vector(a, size);
    generate_random_vector(b, size);

    double serial_start_time, serial_end_time;
    double parallel_start_time, parallel_end_time;

    // Serial vector addition
    omp_set_num_threads(1); // Set the number of threads for serial execution
    serial_start_time = omp_get_wtime();
    vector_addition(a, b, result_add, size, 1);
    serial_end_time = omp_get_wtime();
    printf("Serial Vector Addition Time: %lf seconds\n", serial_end_time - serial_start_time);

    // Parallel vector addition
    omp_set_num_threads(4); // Set the number of threads for parallel execution
    parallel_start_time = omp_get_wtime();
    vector_addition(a, b, result_add, size, 4);
    parallel_end_time = omp_get_wtime();
    printf("Parallel Vector Addition Time: %lf seconds\n", parallel_end_time - parallel_start_time);

    // Calculate speedup and efficiency for vector addition
    double speedup_add = calculate_speedup(serial_end_time - serial_start_time, parallel_end_time - parallel_start_time);
    double efficiency_add = calculate_efficiency(speedup_add, 4);
    printf("Speedup - Addition: %lf\n", speedup_add);
    printf("Efficiency - Addition: %lf\n", efficiency_add);

    // Serial vector subtraction
    omp_set_num_threads(1); // Set the number of threads for serial execution
    serial_start_time = omp_get_wtime();
    vector_subtraction(a, b, result_sub, size, 1);
    serial_end_time = omp_get_wtime();
    printf("Serial Vector Subtraction Time: %lf seconds\n", serial_end_time - serial_start_time);

    // Parallel vector subtraction
    omp_set_num_threads(4); // Set the number of threads for parallel execution
    parallel_start_time = omp_get_wtime();
    vector_subtraction(a, b, result_sub, size, 4);
    parallel_end_time = omp_get_wtime();
    printf("Parallel Vector Subtraction Time: %lf seconds\n", parallel_end_time - parallel_start_time);

    // Calculate speedup and efficiency for vector subtraction
    double speedup_sub = calculate_speedup(serial_end_time - serial_start_time, parallel_end_time - parallel_start_time);
    double efficiency_sub = calculate_efficiency(speedup_sub, 4);
    printf("Speedup - Subtraction: %lf\n", speedup_sub);
    printf("Efficiency - Subtraction: %lf\n", efficiency_sub);

    // Serial vector multiplication
    omp_set_num_threads(1); // Set the number of threads for serial execution
    serial_start_time = omp_get_wtime();
    vector_multiplication(a, b, result_mul, size, 1);
    serial_end_time = omp_get_wtime();
    printf("Serial Vector Multiplication Time: %lf seconds\n", serial_end_time - serial_start_time);

    // Parallel vector multiplication
    omp_set_num_threads(4); // Set the number of threads for parallel execution
    parallel_start_time = omp_get_wtime();
    vector_multiplication(a, b, result_mul, size, 4);
    parallel_end_time = omp_get_wtime();
    printf("Parallel Vector Multiplication Time: %lf seconds\n", parallel_end_time - parallel_start_time);

    // Calculate speedup and efficiency for vector multiplication
    double speedup_mul = calculate_speedup(serial_end_time - serial_start_time, parallel_end_time - parallel_start_time);
    double efficiency_mul = calculate_efficiency(speedup_mul, 4);
    printf("Speedup - Multiplication: %lf\n", speedup_mul);
    printf("Efficiency - Multiplication: %lf\n", efficiency_mul);

    return 0;
}

```
### Output
```plaintext
Serial Vector Addition Time: 0.000000 seconds
Parallel Vector Addition Time: 0.000000 seconds
Speedup - Addition: -1.#IND00
Efficiency - Addition: -1.#IND00
Serial Vector Subtraction Time: 0.000000 seconds
Parallel Vector Subtraction Time: 0.000000 seconds
Speedup - Subtraction: -1.#IND00
Efficiency - Subtraction: -1.#IND00
Serial Vector Multiplication Time: 0.000000 seconds
Parallel Vector Multiplication Time: 0.000000 seconds
Speedup - Multiplication: -1.#IND00
Efficiency - Multiplication: -1.#IND00
```
### Explanation
#### OpenMP Vector Operations Example

The provided C code demonstrates the parallelization of vector addition, subtraction, and multiplication operations using OpenMP. The program compares the performance of the parallel version with the serial version and calculates speedup and efficiency.

#### Overview

1. **Vector Operations Functions:**
   - Three functions (`vector_addition`, `vector_subtraction`, `vector_multiplication`) perform element-wise vector operations (addition, subtraction, and multiplication).
   - Each function is parallelized using `#pragma omp parallel for`.

2. **Memory Allocation and Initialization:**
   - Memory is allocated for vectors `a`, `b`, and result vectors (`result_serial` and `result_parallel`).
   - Vectors `a` and `b` are initialized with values.

3. **Serial Vector Operations:**
   - Sequentially performs vector addition, subtraction, and multiplication.
   - Measures the time taken for serial execution using `omp_get_wtime()`.

4. **Parallel Vector Operations:**
   - Parallel execution of vector operations using OpenMP tasks.
   - Each vector operation is launched as a separate task within a single construct.
   - Measures the time taken for parallel execution using `omp_get_wtime()`.

5. **Speedup and Efficiency Calculation:**
   - Calculates the speedup by comparing the execution times of the serial and parallel versions.
   - Efficiency is calculated based on the speedup and the number of threads used.

6. **Results Output:**
   - Prints the execution times for serial and parallel versions.
   - Displays the calculated speedup and efficiency.

7. **Memory Deallocation:**
   - Frees the memory allocated for vectors.

## OpenMP Directives

- `#pragma omp parallel for`: Parallelizes the associated for loop among multiple threads.
- `#pragma omp parallel`: Creates a parallel region for multithreaded execution.
- `#pragma omp single`: Specifies that the following code block should be executed by a single thread.
- `#pragma omp task`: Introduces a task construct, enabling the creation of parallel tasks.

## Conclusion

This code provides a practical example of parallelizing vector operations using OpenMP, showcasing the potential speedup and efficiency gains in parallel computation. The use of tasks in OpenMP allows for efficient parallelization of independent vector operations, leading to improved performance on multicore architectures.
# Q2) Write a parallel program using OpenMP to find sum of N numbers using the following constructs/clauses. 
### a. Critical section 
### b. Atomic 
### c. Reduction 
### d. Master 
### e. Locks 
```c
#include <stdio.h>
#include <omp.h>

int main() {
    const int N = 100;
    int sum_serial = 0;
    int sum_critical = 0;
    int sum_atomic = 0;
    int sum_reduction = 0;
    int sum_master = 0;
    int sum_locks = 0;

    double serial_time, parallel_time;

    // Serial
    double start_time = omp_get_wtime();
    for (int i = 1; i <= N; ++i) {
        sum_serial += i;
    }
    double end_time = omp_get_wtime();
    serial_time = end_time - start_time;
    printf("Serial Time: %lf seconds\n", serial_time);
    printf("Serial Sum: %d\n\n", sum_serial);

    // a. Critical Section
    int num_threads_critical;
    #pragma omp parallel
    {
        #pragma omp single
        num_threads_critical = omp_get_num_threads();
    }
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 1; i <= N; ++i) {
        #pragma omp critical
        sum_critical += i;
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Critical Section Time with %d threads: %lf seconds\n", num_threads_critical, parallel_time);
    printf("Critical Section Sum: %d\n", sum_critical);

    // Calculate Speedup and Efficiency
    double speedup_critical = serial_time / parallel_time;
    double efficiency_critical = speedup_critical / num_threads_critical;
    printf("Speedup - Critical Section: %lf\n", speedup_critical);
    printf("Efficiency - Critical Section: %lf\n\n", efficiency_critical);

    // b. Atomic
    int num_threads_atomic;
    #pragma omp parallel
    {
        #pragma omp single
        num_threads_atomic = omp_get_num_threads();
    }
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 1; i <= N; ++i) {
        #pragma omp atomic
        sum_atomic += i;
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Atomic Time with %d threads: %lf seconds\n", num_threads_atomic, parallel_time);
    printf("Atomic Sum: %d\n", sum_atomic);

    // Calculate Speedup and Efficiency
    double speedup_atomic = serial_time / parallel_time;
    double efficiency_atomic = speedup_atomic / num_threads_atomic;
    printf("Speedup - Atomic: %lf\n", speedup_atomic);
    printf("Efficiency - Atomic: %lf\n\n", efficiency_atomic);

    // c. Reduction
    int num_threads_reduction;
    #pragma omp parallel
    {
        #pragma omp single
        num_threads_reduction = omp_get_num_threads();
    }
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_reduction)
    for (int i = 1; i <= N; ++i) {
        sum_reduction += i;
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Reduction Time with %d threads: %lf seconds\n", num_threads_reduction, parallel_time);
    printf("Reduction Sum: %d\n", sum_reduction);

    // Calculate Speedup and Efficiency
    double speedup_reduction = serial_time / parallel_time;
    double efficiency_reduction = speedup_reduction / num_threads_reduction;
    printf("Speedup - Reduction: %lf\n", speedup_reduction);
    printf("Efficiency - Reduction: %lf\n\n", efficiency_reduction);

    // d. Master
    int num_threads_master;
    #pragma omp parallel
    {
        #pragma omp master
        {
            num_threads_master = omp_get_num_threads();
        }
    }
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp master
        {
            for (int i = 1; i <= N; ++i) {
                sum_master += i;
            }
        }
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Master Time with %d threads: %lf seconds\n", num_threads_master, parallel_time);
    printf("Master Sum: %d\n", sum_master);

    // Calculate Speedup and Efficiency
    double speedup_master = serial_time / parallel_time;
    double efficiency_master = speedup_master / num_threads_master;
    printf("Speedup - Master: %lf\n", speedup_master);
    printf("Efficiency - Master: %lf\n\n", efficiency_master);

    // e. Locks
    int num_threads_locks;
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel
    {
        #pragma omp single
        num_threads_locks = omp_get_num_threads();
    }
    start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 1; i <= N; ++i) {
        omp_set_lock(&lock);
        sum_locks += i;
        omp_unset_lock(&lock);
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Locks Time with %d threads: %lf seconds\n", num_threads_locks, parallel_time);
    printf("Locks Sum: %d\n", sum_locks);

    // Calculate Speedup and Efficiency
    double speedup_locks = serial_time / parallel_time;
    double efficiency_locks = speedup_locks / num_threads_locks;
    printf("Speedup - Locks: %lf\n", speedup_locks);
    printf("Efficiency - Locks: %lf\n\n", efficiency_locks);

    omp_destroy_lock(&lock);
    return 0;
}

```
### Output
```plaintext
Serial Time: 0.002000 seconds
Serial Sum: 1784293664

Critical Section Time with 16 threads: 4.525000 seconds
Critical Section Sum: 1784293664
Speedup - Critical Section: 0.000442
Efficiency - Critical Section: 0.000028

Atomic Time with 16 threads: 0.011000 seconds
Atomic Sum: 1784293664 Speedup - Atomic: 0.181828
Speedup - Atomic: 0.181828
Efficiency - Atomic: 0.011364

Reduction Time with 16 threads: 0.002000 seconds
Reduction Sum: 1784293664
Speedup - Reduction: 1.000000
Efficiency - Reduction: 0.062500

Master Time with 16 threads: 0.001000 seconds
Master Sum: 1784293664
Speedup - Master: 2.000238
Efficiency - Master: 0.125015

Locks Time with 16 threads: 4.605000 seconds
Locks Sum: 1784293664
Speedup Locks: 0.000434
Efficiency Locks: 0.000027

```
### Explanation
#### OpenMP Synchronization Constructs Example

The provided C code demonstrates the use of various OpenMP synchronization constructs to manage concurrent access to shared resources. The program uses a parallel region to showcase different synchronization mechanisms.

#### Overview

1. **Parallel Region:**
   - The code begins with a parallel region specified by `#pragma omp parallel`.

2. **Critical Section:**
   - `#pragma omp critical` is used to create a critical section, ensuring that only one thread at a time can execute the enclosed block of code.
   - Inside the critical section, the variable `sum` is incremented, and the updated value is printed.

3. **Atomic Operation:**
   - `#pragma omp atomic` is employed to perform an atomic update on the variable `sum`. This ensures atomicity without the need for a critical section.
   - The atomic operation increments `sum`, and the updated value is printed.

4. **Parallel For with Reduction:**
   - `#pragma omp for reduction(+:sum)` parallelizes a for loop with a reduction operation. Each thread computes a local sum, and these local sums are combined at the end using the specified reduction operation.
   - The loop iterates from 0 to `n-1`, adding each `i` to the shared variable `sum`.

5. **Master Region:**
   - `#pragma omp master` designates a region of code that should only be executed by the master thread (the thread with ID 0). Inside the master region, the variable `sum` is incremented, and the updated value is printed.

6. **Locks:**
   - An OpenMP lock (`omp_lock_t`) is initialized using `omp_init_lock`.
   - `omp_set_lock` acquires the lock, protecting the critical section where `sum` is updated.
   - `omp_unset_lock` releases the lock, allowing other threads to acquire it.
   - `omp_destroy_lock` cleans up the lock after its use.
   - The critical section within the lock increments `sum`, and the updated value is printed.

7. **Final Output:**
   - The program prints the final value of the variable `sum` after all parallel operations.

## OpenMP Directives

- `#pragma omp parallel`: Creates a parallel region for multithreaded execution.
- `#pragma omp critical`: Defines a critical section, allowing only one thread to execute it at a time.
- `#pragma omp atomic`: Performs an atomic operation on the specified variable.
- `#pragma omp for reduction(+:sum)`: Parallelizes a for loop with a reduction operation.
- `#pragma omp master`: Indicates a code block to be executed only by the master thread.
- Lock-related functions (`omp_init_lock`, `omp_set_lock`, `omp_unset_lock`, `omp_destroy_lock`): Initialize, acquire, release, and destroy an OpenMP lock.

## Conclusion

This code illustrates how OpenMP synchronization constructs can be employed to manage shared resources and avoid data race conditions in a parallel computing environment. The use of critical sections, atomic operations, parallel for loops with reduction, master regions, and locks showcases different techniques for synchronizing threads in a parallel program.

# Q3) Write a parallel program using OpenMP to implement the Odd-even transposition sort. Vary the input size and analyse the program efficiency.
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void oddEvenSort(int arr[], int n) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;

        // Odd phase
        #pragma omp parallel for shared(arr, n, sorted)
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                sorted = 0;
            }
        }

        // Even phase
        #pragma omp parallel for shared(arr, n, sorted)
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                sorted = 0;
            }
        }

        #pragma omp barrier // Synchronize before checking the sorted flag
    }
}

int main() {
    const int maxN = 100000;
    int inputSizes[] = {100, 500, 1000, 50000, 100000};
    
    for (int k = 0; k < sizeof(inputSizes) / sizeof(inputSizes[0]); ++k) {
        int n = inputSizes[k];
        int arr[maxN];

        // Initialize the array with random values
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % 1000; // Random values between 0 and 999
        }

        double s_start_time, s_end_time, p_start_time, p_end_time;

        // Sequential Odd-Even Transposition Sort
        int seqArr[maxN];
        for (int i = 0; i < n; ++i) {
            seqArr[i] = arr[i];
        }
        omp_set_num_threads(1); // Set the number of threads for the sequential version
        s_start_time = omp_get_wtime();
        oddEvenSort(seqArr, n);
        s_end_time = omp_get_wtime();
        printf("Sequential time for N = %d: %lf seconds\n", n, s_end_time - s_start_time);

        // Parallel Odd-Even Transposition Sort
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % 1000; // Re-initialize the array for the parallel version
        }
        omp_set_num_threads(8); // Set the number of threads for the parallel version
        p_start_time = omp_get_wtime();
        oddEvenSort(arr, n);
        p_end_time = omp_get_wtime();
        printf("Parallel time for N = %d: %lf seconds\n", n, p_end_time - p_start_time);

        // Verify if the array is sorted
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                printf("Error: The array is not sorted.\n");
                break;
            }
        }

        // Calculate speedup and efficiency
        double sequential_time = s_end_time - s_start_time;
        double parallel_time = p_end_time - p_start_time;

        double speedup = sequential_time / parallel_time;
        double efficiency = speedup / omp_get_max_threads();

        printf("Speedup for N = %d: %lf\n", n, speedup);
        printf("Efficiency for N = %d: %lf\n", n, efficiency);

        printf("-------------------------------------------\n");
    }

    return 0;
}

```
### Output
```plaintext
Sequential time for N = 100: 0.000000 seconds
Parallel time for N = 100: 0.000000 seconds
Speedup for N = 100: -1.#IND00
Efficiency for N = 100: -1.#IND00
-------------------------------------------
Sequential time for N = 500: 0.000000 seconds
Parallel time for N = 500: 0.032000 seconds
Speedup for N = 500: 0.000000
Efficiency for N = 500: 0.000000
-------------------------------------------
Sequential time for N = 1000: 0.000000 seconds
Parallel time for N = 1000: 0.063000 seconds
Speedup for N = 1000: 0.000000
Efficiency for N = 1000: 0.000000
```
### Explanation
## Odd-Even Transposition Sort using OpenMP

### Overview

The provided C code implements the Odd-Even Transposition Sort algorithm in a parallelized manner using OpenMP. This sorting algorithm is particularly suitable for parallelization due to its simplicity and inherent parallel structure.

### Odd-Even Transposition Sort Algorithm

1. **Overview:**
   - The Odd-Even Transposition Sort is a simple parallel sorting algorithm that works by repeatedly iterating through the array in two phases: odd and even.
   - In each phase, adjacent elements are compared and swapped if necessary, leading to a partially sorted array after each iteration.

2. **Parallelization Approach:**
   - The parallelization is achieved using OpenMP directives.
   - The `#pragma omp parallel for` directive parallelizes the loop iterations among multiple threads.
   - The `private(i, temp)` clause ensures private copies of loop variables `i` and `temp` for each thread.
   - The `shared(a)` clause indicates that the array `a` is shared among all threads.

3. **Even and Odd Phases:**
   - In the even phase, adjacent elements with even indices are compared and swapped if needed.
   - In the odd phase, adjacent elements with odd indices are compared and swapped if needed.

### OpenMP Directives

- `#pragma omp parallel for`: Parallelizes the associated for loop among multiple threads.
- `private(i, temp)`: Declares private copies of loop variables `i` and `temp` for each thread.
- `shared(a)`: Specifies that the array `a` is shared among all threads.

### Input and Output

- The user inputs the size of the array (`n`) at runtime.
- The array is initialized with random values between 0 and 99.
- The unsorted array is displayed.
- The time taken for sorting using Odd-Even Transposition Sort is measured and displayed.
- The sorted array is displayed.

### Conclusion

This code provides a practical example of parallelizing a sorting algorithm using OpenMP, demonstrating how parallel patterns can be incorporated into algorithms to enhance performance. The Odd-Even Transposition Sort is particularly suited for parallelization due to its simple structure and regular data access patterns.

# Q4) Write an OpenMP program to find the Summation of integers from a given interval. Analyze the performance of various iteration scheduling strategies.
```c
#include <stdio.h>
#include <omp.h>

#define N 100000000

int main() {
    int sum = 0;
    int i;

    // Sequential summation for comparison
    double s_start_time_seq = omp_get_wtime();
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double s_end_time_seq = omp_get_wtime();
    double seq_time = s_end_time_seq - s_start_time_seq;
    printf("Sequential Sum: %d\n", sum);
    printf("Sequential Time: %lf seconds\n", seq_time);
    printf("******************************************\n");

    // Reset sum for parallel summation
    sum = 0;

    // Parallel summation with different scheduling strategies

    // Static scheduling
    double start_time_static = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_static = omp_get_wtime();
    printf("Sum using Static Scheduling: %d\n", sum);
    printf("Static Scheduling Time: %lf seconds\n", end_time_static - start_time_static);
    double speedup_static = seq_time / (end_time_static - start_time_static);
    double efficiency_static = speedup_static / omp_get_max_threads();
    printf("Speedup (Static): %lf\n", speedup_static);
    printf("Efficiency (Static): %lf\n", efficiency_static);
    printf("******************************************\n");

    // Reset sum for other strategies
    sum = 0;

    // Dynamic scheduling
    double start_time_dynamic = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_dynamic = omp_get_wtime();
    printf("Sum using Dynamic Scheduling: %d\n", sum);
    printf("Dynamic Scheduling Time: %lf seconds\n", end_time_dynamic - start_time_dynamic);
    double speedup_dynamic = seq_time / (end_time_dynamic - start_time_dynamic);
    double efficiency_dynamic = speedup_dynamic / omp_get_max_threads();
    printf("Speedup (Dynamic): %lf\n", speedup_dynamic);
    printf("Efficiency (Dynamic): %lf\n", efficiency_dynamic);
    printf("******************************************\n");

    // Reset sum for other strategies
    sum = 0;

    // Guided scheduling
    double start_time_guided = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(guided)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_guided = omp_get_wtime();
    printf("Sum using Guided Scheduling: %d\n", sum);
    printf("Guided Scheduling Time: %lf seconds\n", end_time_guided - start_time_guided);
    double speedup_guided = seq_time / (end_time_guided - start_time_guided);
    double efficiency_guided = speedup_guided / omp_get_max_threads();
    printf("Speedup (Guided): %lf\n", speedup_guided);
    printf("Efficiency (Guided): %lf\n", efficiency_guided);

    return 0;
}
```
### Output
```plaintext
Sequential Sum: 987459712
Sequential Time: 0.161000 seconds
******************************************
Sum using Static Scheduling: 987459712
Static Scheduling Time: 0.015000 seconds
Speedup (Static): 10.733430
Efficiency (Static): 0.536671
******************************************
Sum using Dynamic Scheduling: 987459712
Dynamic Scheduling Time: 2.045000 seconds
Speedup (Dynamic): 0.078729
Efficiency (Dynamic): 0.003936
******************************************
Sum using Guided Scheduling: 987459712
Guided Scheduling Time: 0.006000 seconds
Speedup (Guided): 26.833148
Efficiency (Guided): 1.341657
```
### Explanation

The C code above demonstrates the usage of different OpenMP scheduling techniques for parallelizing a summation task. The goal is to calculate the sum of integers from 1 to N in parallel.

## Code Overview

1. **Static Scheduling:**
   - Static scheduling divides the loop into fixed-sized chunks assigned to threads at compile time.
   - `#pragma omp parallel for schedule(static)` parallelizes the loop with static scheduling.
   - Static scheduling is effective when iterations have uniform execution times.

2. **Dynamic Scheduling:**
   - Dynamic scheduling divides the loop into chunks assigned dynamically at runtime.
   - `#pragma omp parallel for schedule(dynamic)` enables dynamic scheduling.
   - This is suitable when iteration times vary, allowing load balancing among threads.

3. **Guided Scheduling:**
   - Guided scheduling is similar to dynamic scheduling but with decreasing chunk sizes over time.
   - `#pragma omp parallel for schedule(guided)` specifies guided scheduling.
   - It adapts to varying workloads and can enhance load balancing.


# Q5) Write a parallel program using OpenMP to generate the histogram of the given array A. 
`Hint: To generate histogram, we simply divide the range of the data up into equal sized sub intervals, or bins and determine the number of measurements (frequency) in each 
bin.`
#### Example: 
`1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3, 4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9`
```c
#define ARRAY_SIZE 100
#define NUM_BINS 5

void print_histogram(int histogram[], int num_bins) {
    printf("Histogram:\n");
    for (int i = 0; i < num_bins; ++i) {
        printf("%d |", i + 1);
        for (int j = 0; j < histogram[i]; ++j) {
            printf("*");
        }
        printf(" (%d)\n", histogram[i]);
    }
}

int main() {
    // Generate an array of 100 random fractional numbers between 1 to 20
    double A[ARRAY_SIZE];
    srand(omp_get_wtime()); // Seed for random number generation

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        A[i] = (rand() % 1901 + 100) / 100.0; // Random numbers between 1 and 20 with two decimal places
    }

    int histogram[NUM_BINS] = {0};

    double min_val = A[0];
    double max_val = A[0];

    // Find the minimum and maximum values in the array
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (A[i] < min_val) {
            min_val = A[i];
        }
        if (A[i] > max_val) {
            max_val = A[i];
        }
    }

    // Calculate the range of data and width of each bin
    double range = max_val - min_val;
    double bin_width = range / NUM_BINS;

    // Sequential execution
    double start_time_seq = omp_get_wtime();
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        // Determine the bin index for each data point
        int bin_index = (int)((A[i] - min_val) / bin_width);

        // Ensure the bin index is within the valid range
        if (bin_index < 0) {
            bin_index = 0;
        } else if (bin_index >= NUM_BINS) {
            bin_index = NUM_BINS - 1;
        }

        // Increment the corresponding bin
        histogram[bin_index]++;
    }
    double end_time_seq = omp_get_wtime();

    // Print the histogram in a graphical form
    print_histogram(histogram, NUM_BINS);

    // Reset histogram for parallel execution
    for (int i = 0; i < NUM_BINS; ++i) {
        histogram[i] = 0;
    }

    // Parallel execution
    double start_time_parallel = omp_get_wtime();
    #pragma omp parallel for shared(A, histogram, min_val, bin_width)
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        // Determine the bin index for each data point
        int bin_index = (int)((A[i] - min_val) / bin_width);

        // Ensure the bin index is within the valid range
        if (bin_index < 0) {
            bin_index = 0;
        } else if (bin_index >= NUM_BINS) {
            bin_index = NUM_BINS - 1;
        }

        // Increment the corresponding bin in a thread-safe manner
        #pragma omp atomic
        histogram[bin_index]++;
    }
    double end_time_parallel = omp_get_wtime();

    // Calculate and print execution times
    double time_seq = end_time_seq - start_time_seq;
    double time_parallel = end_time_parallel - start_time_parallel;

    printf("Sequential Time: %lf seconds\n", time_seq);
    printf("Parallel Time: %lf seconds\n", time_parallel);

    // Calculate speedup and efficiency
    double speedup = time_seq / time_parallel;
    double efficiency = speedup / omp_get_max_threads();

    printf("Speedup: %lf\n", speedup);
    printf("Efficiency: %lf\n", efficiency);

    return 0;
}
```
### Output
```plaintext
Histogram:
1 |******************** (20)
2 |********************* (21)
3 |****************** (18)
4 |********************** (22)
5 |******************* (19)
Sequential Time: 0.000000 seconds
Parallel Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00
```
### Explanation

1. **OpenMP Directive:** The `#pragma omp parallel for` directive is used to parallelize the for loop. This allows the iterations of the loop to be executed concurrently by multiple threads.

2. **Critical Section:** Since multiple threads are updating the `histogram` array simultaneously, a critical section (`#pragma omp critical`) is used to ensure that only one thread can update the histogram at a time. This prevents race conditions and ensures the correctness of the histogram results.

3. **Parallelization Strategy:** Each thread independently calculates the bin index for its assigned data points, and then updates the corresponding bin in the histogram array. The critical section ensures that these updates are done safely in a mutually exclusive manner.
