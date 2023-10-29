# Banker's Algorithm - Question 8.1

This program implements the Banker's algorithm for deadlock avoidance. It accepts user inputs for resource allocation and request scenarios, and it checks if the system is in a safe state or not.

## Problem Statement

(a) What is the content of the matrix Need?

(b) Is the system in a safe state?

(c) If a request from process P1 arrives for (1, 0, 2), can the request be granted immediately? Display the updated Allocation, Need, and Available matrices.

(d) If a request from process P4 arrives for (3, 3, 0), can the request be granted immediately?

(e) If a request from process P0 arrives for (0, 2, 0), can the request be granted immediately?

## Solution

```cpp
#include <stdio.h>

int main() {
    int n, m, i, j, k;
    n = 5; // Number of processes
    m = 3; // Number of resource types

    // Allocation Matrix: Represents the resources allocated to each process
    int alloc[5][3] = {
        { 0, 1, 0 }, // Allocation for process P0
        { 2, 0, 0 }, // Allocation for process P1
        { 3, 0, 2 }, // Allocation for process P2
        { 2, 1, 1 }, // Allocation for process P3
        { 0, 0, 2 }  // Allocation for process P4
    };

    // MAX Matrix: Represents the maximum demand of resources for each process
    int max[5][3] = {
        { 7, 5, 3 }, // Maximum demand for process P0
        { 3, 2, 2 }, // Maximum demand for process P1
        { 9, 0, 2 }, // Maximum demand for process P2
        { 2, 2, 2 }, // Maximum demand for process P3
        { 4, 3, 3 }  // Maximum demand for process P4
    };

    // Available Resources: Represents the currently available instances of each resource type
    int avail[3] = { 3, 3, 2 };

    int f[5], ans[5], ind = 0; // Arrays to track process status and the safe sequence
    for (k = 0; k < n; k++) {
        f[k] = 0; // Initialize all processes as not finished
    }

    // Calculate the resource needs for each process (need matrix)
    int need[5][3]; // Matrix to represent the resource needs of each process
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j]; // Calculate the resource needs
    }

    int y = 0;
    // Iterate through the processes to determine the safe sequence
    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1; // Set a flag if the process can't be executed
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i; // Process can be executed, add it to the safe sequence
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y]; // Update available resources
                    f[i] = 1; // Mark the process as finished
                }
            }
        }
    }

    int flag = 1;
    // Check if all processes have been marked as finished
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The given sequence is not safe\n");
            break;
        }
    }

    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        // Print the safe sequence
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;
}

```
# Problem Statement

**Problem**: Given a set of processes and the resources each process requires, determine if there is a safe sequence in which these processes can be executed without causing a deadlock.

## Input

- `n`: Number of processes.
- `m`: Number of resource types.
- `alloc`: A 2D array representing the allocation matrix, indicating the number of resources each process currently holds.
- `max`: A 2D array representing the maximum demand matrix, indicating the maximum number of each resource that each process may request.
- `avail`: An array representing the available instances of each resource type.

## Output

- If a safe sequence exists, provide the sequence in which the processes can be executed.
- If there is no safe sequence, indicate that the given sequence is not safe.

# Explanation

## Concept

This problem involves resource allocation and deadlock detection using the Banker's Algorithm. The Banker's Algorithm is used to determine if a set of processes can be executed in a way that avoids a deadlock. A safe sequence is a sequence of processes in which each process can complete its execution without waiting indefinitely for resources.

## Steps to Determine a Safe Sequence

1. Calculate the `need` matrix: The need matrix represents the remaining resources needed by each process to complete its execution. It is calculated by subtracting the `alloc` matrix from the `max` matrix.

2. Initialize data structures:
   - `avail` represents the available instances of each resource type.
   - `f` is an array to track the finish status of each process.
   - `ans` is an array to store the safe sequence.
   - `ind` is an index used to keep track of the safe sequence.

3. Iterate through the processes to determine the safe sequence:
   - Check if a process is not finished (`f[i] == 0`).
   - If the process can execute (i.e., its resource needs are less than or equal to the available resources), mark it as finished (`f[i] = 1`), update the available resources, and add the process to the safe sequence (`ans[ind++] = i`).

4. After iterating through all processes, check if all processes have been marked as finished. If yes, a safe sequence exists. If not, there is no safe sequence.

# Code

The C code provided earlier in this conversation implements the Banker's Algorithm to determine a safe sequence for the given inputs.

# Output

The output of the code will either provide a safe sequence or indicate that the given sequence is not safe.

![Alt text](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/week8_1.png)
