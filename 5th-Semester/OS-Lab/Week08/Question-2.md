# Deadlock Detection Algorithm - Question 8.2

This program implements the deadlock detection algorithm for a system with multiple processes and resources. The algorithm checks if there is a safe state for the system, where a safe state is one in which all processes can finish execution.

## Problem Statement

### Consider the following snapshot of the system. Write a C program to implement the deadlock detection algorithm.

(a) Is the system in a safe state?

(b) Suppose that process P2 makes one additional request for an instance of type C, can the system still be in a safe state?

## System State Tables

### Allocation 

| | A | B | C |
|-|-|-|-|  
| P0 | 0 | 1 | 0 |
| P1 | 2 | 0 | 0 |  
| P2 | 3 | 0 | 3 |
| P3 | 2 | 1 | 1 |
| P4 | 0 | 0 | 2 |

### Request

| | A | B | C |
|-|-|-|-|
| P0 | 0 | 0 | 0 |  
| P1 | 2 | 0 | 2 |
| P2 | 0 | 0 | 0 |
| P3 | 1 | 0 | 0 |
| P4 | 0 | 0 | 2 |

### Available

| A | B | C |
|-|-|-|
| 0 | 0 | 0 |

## Code Snippet

```c
#include <stdio.h>

// Define the number of processes and resources
#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

// Define data structures to store the system state
typedef struct {
  int allocation[NUM_RESOURCES];
  int request[NUM_RESOURCES];
} Process;

// Define global variables for system state
Process processes[NUM_PROCESSES] = {
  {{0, 1, 0}, {0, 0, 0}}, 
  {{2, 0, 0}, {2, 0, 2}},
  {{3, 0, 3}, {0, 0, 0}},
  {{2, 1, 1}, {1, 0, 0}},
  {{0, 0, 2}, {0, 0, 2}}
};

int available[NUM_RESOURCES] = {0, 0, 0};

// Function to check if a process is finished
int is_process_finished(int process_id) {
  for (int i = 0; i < NUM_RESOURCES; i++) {
    if (processes[process_id].allocation[i] + processes[process_id].request[i] != 0) {
      return 0; // Process is not finished
    }
  }
  return 1; // Process is finished
}

// Function to check if the system is in a safe state
int is_safe_state() {
  int work[NUM_RESOURCES];
  int finish[NUM_PROCESSES];

  // Initialize work and finish arrays
  for (int i = 0; i < NUM_RESOURCES; i++) {
    work[i] = available[i];
  }
  for (int i = 0; i < NUM_PROCESSES; i++) {
    finish[i] = is_process_finished(i);
  }

  // Check for a safe state
  int count = 0;
  while (count < NUM_PROCESSES) {
    int found = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
      if (finish[i] == 0) {
        int j;
        for (j = 0; j < NUM_RESOURCES; j++) {
          if (processes[i].request[j] > work[j]) {
            break;
          }
        }
        if (j == NUM_RESOURCES) {
          // Process can complete
          for (int k = 0; k < NUM_RESOURCES; k++) {
            work[k] += processes[i].allocation[k];
          }
          finish[i] = 1;
          found = 1;
          count++;
        }
      }
    }
    if (!found) {
      break;
    }
  }

  return (count == NUM_PROCESSES);
}

int main() {
  // Check if the system is in a safe state
  if (is_safe_state()) {
    printf("The system is in a safe state.\n");
  } else {
    printf("The system is not in a safe state.\n");
  }

  // Additional request from P2
  processes[2].request[2] = 1;

  // Check if the system is still in a safe state
  if (is_safe_state()) {
    printf("The system is in a safe state after P2's additional request.\n");
  } else {
    printf("The system is not in a safe state after P2's additional request.\n");
  }

  return 0;
}

```
# Code Explanation

This section provides a detailed explanation of how the code works.

## Initialization

- The code begins by defining the number of processes and resource types using `NUM_PROCESSES` and `NUM_RESOURCES` constants.

- It defines a `Process` struct to represent each process's allocation and request arrays.

- The `processes` array represents the current state of the system, including the allocation and request of each process.

- The `available` array holds the available instances of each resource type.

## Function Explanation

### `is_process_finished(process_id)`

- This function checks if a process has finished its execution by examining its allocation and request arrays.

### `is_safe_state()`

- The `is_safe_state` function implements the Banker's Algorithm, which checks if the system is in a safe state.

- It initializes `work` and `finish` arrays, where `work` represents the available resources and `finish` tracks whether each process has finished.

- The function then simulates resource allocation:
  - It checks if any process can be executed based on its request and available resources.
  - If a process can be executed, it marks the process as finished, updates the available resources, and increments the `count` of finished processes.

- The function returns `1` if all processes can complete (system is in a safe state) and `0` otherwise.

## Code Execution

1. The code checks if the system is in a safe state using the `is_safe_state` function. If the system is safe, it prints that the system is in a safe state. Otherwise, it prints that the system is not in a safe state.

2. An additional resource request is made by process P2. The code then checks if the system remains in a safe state after the request.

## Output

The output of the code will indicate whether the system is in a safe state and whether it remains safe after an additional request.

![Alt text](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/week8_2.png)

