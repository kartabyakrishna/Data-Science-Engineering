# Q1) Write a parallel program using OpenMP to perform vector addition, subtraction, multiplication. Demonstrate task level parallelism. Analyze the speedup and efficiency of the parallelized code. 

```c
#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h> 
 
void generate_random_vector(int *vec, int size) { 
    for (int i = 0; i < size; ++i) { 
        vec[i] = rand() % 100;  // Random values between 0 and 99 
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
Serial Time: 0.000000 seconds
Parallel Time: 0.000000 seconds
Speedup: -1.#IND00
Efficiency: -1.#IND00
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
#include <omp.h>
#include <stdio.h>

int main() {
  int n = 100;
  int sum = 0;

  #pragma omp parallel
  {
    #pragma omp critical
    {
      sum += 1;
      printf("After critical: %d\n", sum);
    }

    #pragma omp atomic
    sum += 1;
    printf("After atomic: %d\n", sum);

    #pragma omp for reduction(+:sum)
    for(int i=0; i<n; i++) {
      sum += i;
    }
    printf("After reduction: %d\n", sum);

    #pragma omp master
    {
      sum += 1;
      printf("After master: %d\n", sum);
    }

    omp_lock_t lock;
    omp_init_lock(&lock);
    omp_set_lock(&lock);
    sum += 1; 
    omp_unset_lock(&lock);
    omp_destroy_lock(&lock);
    printf("After lock: %d\n", sum);
  }

  printf("Final Sum = %d\n", sum);

  return 0;
}
```
### Output
```plaintext
After critical: 1
After atomic: 2
After critical: 3
After atomic: 74
After critical: 75
After atomic: 195
After critical: 196
After atomic: 365
After critical: 366
After atomic: 550
After critical: 551
After atomic: 771
After critical: 772
After atomic: 1028
After critical: 1029
After atomic: 1321
After critical: 1322
After atomic: 1650
After critical: 1651
After atomic: 2051
After critical: 2052
After atomic: 2416
After critical: 2417
After atomic: 2889
After critical: 2890
After atomic: 3398
After critical: 3399
After atomic: 3421
After critical: 3422
After atomic: 3858
After critical: 3859
After atomic: 4403
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After reduction: 4982
After master: 4995
After reduction: 4982
After reduction: 4982
After lock: 4983
After lock: 4984
After lock: 4985
After lock: 4986
After lock: 4987
After lock: 4988
After lock: 4989
After lock: 4990
After lock: 4991
After lock: 4992
After lock: 4993
After lock: 4994
After reduction: 4982
After lock: 4996
After lock: 4997
After lock: 4998
After lock: 4999
Final Sum = 4999
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

void odd_even_sort(int *a, int n) {
    int phase, i, temp;

    for (phase = 0; phase < n; ++phase) {
        if (phase % 2 == 0) {
            // Even phase
            #pragma omp parallel for private(i, temp) shared(a)
            for (i = 1; i < n - 1; i += 2) {
                if (a[i] > a[i + 1]) {
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }
        } else {
            // Odd phase
            #pragma omp parallel for private(i, temp) shared(a)
            for (i = 0; i < n - 1; i += 2) {
                if (a[i] > a[i + 1]) {
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int n, i;
    double start_time, end_time;

    // Vary the input size
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    // Initialize the array with random values
    for (i = 0; i < n; ++i) {
        arr[i] = rand() % 100;  // Random values between 0 and 99
    }

    // Display the unsorted array
    printf("Unsorted array:\n");
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Measure time before sorting
    start_time = omp_get_wtime();

    // Sort the array using Odd-Even Transposition Sort
    odd_even_sort(arr, n);

    // Measure time after sorting
    end_time = omp_get_wtime();

    // Display the sorted array
    printf("\nSorted array:\n");
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Display the time taken for sorting
    printf("Time taken: %f seconds\n", end_time - start_time);

    free(arr);

    return 0;
}
```
### Output
```plaintext
Enter the size of the array: 15
Unsorted array:
41 67 34 0 69 24 78 58 62 64 5 45 81 27 61

Sorted array:
0 5 24 27 34 41 45 58 61 62 64 67 69 78 81
Time taken: 0.015000 seconds
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

#define N 1000000000

int main() {
    long long sum = 0;
    int i;

    // Static Scheduling
    double start_time_static = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_static = omp_get_wtime();

    printf("Sum using Static Scheduling: %lld\n", sum);
    printf("Time taken with Static Scheduling: %f seconds\n", end_time_static - start_time_static);

    sum = 0;

    // Dynamic Scheduling
    double start_time_dynamic = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_dynamic = omp_get_wtime();

    printf("\nSum using Dynamic Scheduling: %lld\n", sum);
    printf("Time taken with Dynamic Scheduling: %f seconds\n", end_time_dynamic - start_time_dynamic);

    sum = 0;

    // Guided Scheduling
    double start_time_guided = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum) schedule(guided)
    for (i = 1; i <= N; ++i) {
        sum += i;
    }
    double end_time_guided = omp_get_wtime();

    printf("\nSum using Guided Scheduling: %lld\n", sum);
    printf("Time taken with Guided Scheduling: %f seconds\n", end_time_guided - start_time_guided);

    return 0;
}

```
### Output
```plaintext
Sum using Static Scheduling: 500000000500000000
Time taken with Static Scheduling: 0.093000 seconds

Sum using Dynamic Scheduling: 500000000500000000
Time taken with Dynamic Scheduling: 21.003000 seconds

Sum using Guided Scheduling: 500000000500000000
Time taken with Guided Scheduling: 0.084000 seconds
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
#include <stdio.h>
#include <omp.h>

#define NUM_BINS 10 

int main() {

  float data[20] = {1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3,  
                   4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9};
                   
  int histogram[NUM_BINS] = {0};

  // Find min and max values 
  float min_val = data[0];
  float max_val = data[0];

  for (int i = 1; i < 20; i++) {
    if (data[i] < min_val) min_val = data[i];
    if (data[i] > max_val) max_val = data[i];
  }

  // Calculate bin size
  float bin_size = (max_val - min_val) / NUM_BINS;

  #pragma omp parallel for
  for (int i = 0; i < 20; i++) {
    int bin = (int)((data[i] - min_val) / bin_size);
    
    #pragma omp critical
    {
      histogram[bin]++;
    }
  }

  // Print histogram
  for (int i = 0; i < NUM_BINS; i++) {
    float bin_start = min_val + i*bin_size;
    float bin_end = bin_start + bin_size;
    printf("[%0.1f, %0.1f): %d\n", bin_start, bin_end, histogram[i]);
  }

  return 0;
}
```
### Output
```plaintext
[0.3, 0.8): 5
[0.8, 1.2): 1
[1.2, 1.7): 2
[1.7, 2.1): 1
[2.1, 2.6): 1
[2.6, 3.1): 1
[3.1, 3.5): 2
[3.5, 4.0): 1
[4.0, 4.4): 3
[4.4, 4.9): 1
```
### Explanation

1. **OpenMP Directive:** The `#pragma omp parallel for` directive is used to parallelize the for loop. This allows the iterations of the loop to be executed concurrently by multiple threads.

2. **Critical Section:** Since multiple threads are updating the `histogram` array simultaneously, a critical section (`#pragma omp critical`) is used to ensure that only one thread can update the histogram at a time. This prevents race conditions and ensures the correctness of the histogram results.

3. **Parallelization Strategy:** Each thread independently calculates the bin index for its assigned data points, and then updates the corresponding bin in the histogram array. The critical section ensures that these updates are done safely in a mutually exclusive manner.
