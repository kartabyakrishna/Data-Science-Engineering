# Q1 . Write a simple MPI program to find out pow (x, rank) for all the processes where 'x' is the integer constant and 'rank' is the rank of the process.
```c
#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Assuming x is a constant value
    int x = 40;

    double result = pow(x, world_rank);

    printf("Process %d: pow(%d, %d) = %f\n", world_rank, x, world_rank, result);

    MPI_Finalize();
    return 0;
}
```
## Output :  
```plaintext
PS C:\Users\mca\source\repos\210968244\x64\Debug> mpiexec -n 5 210968244.exe
Process 2: pow(40, 2) = 1600.000000
Process 1: pow(40, 1) = 40.000000
Process 0: pow(40, 0) = 1.000000
Process 4: pow(40, 4) = 2560000.000000
Process 3: pow(40, 3) = 64000.000000
```
## Explanaion

- The program initializes MPI environment, gets the total number of processes (world_size) and the rank of the current process (world_rank).

- An integer constant x is assumed with a value of 40.

- Each process calculates pow(x, world_rank), i.e., x raised to the power of its rank.

- The result of this calculation is printed for each process using printf().

- Finally, MPI environment is finalized using MPI_Finalize().
---
# Q2. Write a program in MPI where even ranked process prints "Hello" and odd ranked process prints "World".
```c
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank % 2 == 0) {
        printf(" EVEN Hello from process %d\n", world_rank);
    }
    else {
        printf("ODD World from process %d\n", world_rank);
    }

    MPI_Finalize();
    return 0;
}
```
## Output :  
```plaintext
PS C:\Users\mca\source\repos\210968244\x64\Debug> mpiexec -n 14 210968244.exe
ODD World from process 13
EVEN Hello from process 2
ODD World from process 9
ODD World from process 1
EVEN Hello from process 8
EVEN Hello from process 12
ODD World from process 5
ODD World from process 3
ODD World from process 11
EVEN Hello from process 6
EVEN Hello from process 0
EVEN Hello from process 4
ODD World from process 7
EVEN Hello from process 10
```
## Explanation:

- The program initializes MPI environment, gets the total number of processes (`world_size`) and the rank of the current process (`world_rank`).
  
- It then checks if the rank of the current process is even or odd using the modulo operator `% 2`.

- If the rank is even (`world_rank % 2 == 0`), the process prints "EVEN Hello" along with its rank using `printf()`.

- If the rank is odd, the process prints "ODD World" along with its rank using `printf()`.

- Finally, MPI environment is finalized using `MPI_Finalize()`.
- 
---

# Q3. Write a program in MPI to simulate simple calculator. Perform each operation using different process in parallel.
```c
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char operations[] = { '+', '-', '*', '/' };
    char operation = operations[world_rank % 4];

    double operand1 = 10.0, operand2 = 2.0;
    double result = 0.0;

    switch (operation) {
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        if (operand2 != 0) {
            result = operand1 / operand2;
        }
        else {
            fprintf(stderr, "Error: Division by zero.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        break;
    default:
        fprintf(stderr, "Error: Unknown operation.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Allocate memory dynamically for gathered_results
    double* gathered_results = (double*)malloc(world_size * sizeof(double));

    MPI_Gather(&result, 1, MPI_DOUBLE, gathered_results, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Results:\n");
        for (int i = 0; i < world_size; ++i) {
            printf("Process %d: %.2f %c %.2f = %.2f\n", i, operand1, operations[i % 4], operand2, gathered_results[i]);
        }
    }

    // Free dynamically allocated memory
    free(gathered_results);

    MPI_Finalize();
    return 0;
}
```

## Output :  
```plaintext
PS C:\Users\mca\source\repos\210968244\x64\Debug> mpiexec -n 14 210968244.exe
Results:
Process 0: 10.00 + 2.00 = 12.00
Process 1: 10.00 - 2.00 = 8.00
Process 2: 10.00 * 2.00 = 20.00
Process 3: 10.00 / 2.00 = 5.00
Process 4: 10.00 + 2.00 = 12.00
Process 5: 10.00 - 2.00 = 8.00
Process 6: 10.00 * 2.00 = 20.00
Process 7: 10.00 / 2.00 = 5.00
Process 8: 10.00 + 2.00 = 12.00
Process 9: 10.00 - 2.00 = 8.00
Process 10: 10.00 * 2.00 = 20.00
Process 11: 10.00 / 2.00 = 5.00
Process 12: 10.00 + 2.00 = 12.00
Process 13: 10.00 - 2.00 = 8.00
```
## Explanation

- The program initializes MPI environment, gets the total number of processes (`world_size`) and the rank of the current process (`world_rank`).

- An array `operations[]` is defined to store different arithmetic operations: addition (`+`), subtraction (`-`), multiplication (`*`), and division (`/`).

- Each process selects an operation based on its rank using modulo operator `% 4` to cycle through the operations.

- Two operands `operand1` and `operand2` are initialized with values 10.0 and 2.0 respectively.

- A `switch` statement is used to perform the selected operation on `operand1` and `operand2`. If division is selected, it checks for division by zero.

- Memory is dynamically allocated for an array `gathered_results` to gather the results from all processes.

- MPI_Gather function is used to collect the result from each process into the `gathered_results` array on the root process (rank 0).

- If the current process is the root process (rank 0), it prints the gathered results along with the corresponding operations performed.
---
- Finally, dynamically allocated memory for `gathered_results` is freed and MPI environment is finalized using `MPI_Finalize()`.
---
# Q4. Write a program in MPI to toggle the character of a given string indexed by the rank of theprocess. 
### Hint: Suppose the string is HeLLO and there are 5 processes, then process 0 toggle 'H' to 'h', process 1 toggle 'e' to 'E' and so on. 

```c
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAX_STRING_SIZE 100

int main(int argc, char *argv[]) {
    int rank, size;
    char str[MAX_STRING_SIZE] = "HeLLO";
    int str_len;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    str_len = strlen(str);

    // Determine the character index to toggle based on process rank
    int char_index = rank % str_len;

    // Toggle the character
    if (rank < str_len) {
        if (str[char_index] >= 'a' && str[char_index] <= 'z') {
            str[char_index] = str[char_index] - 32; // Convert to uppercase
        } else if (str[char_index] >= 'A' && str[char_index] <= 'Z') {
            str[char_index] = str[char_index] + 32; // Convert to lowercase
        }
    }

    // Gather all modified strings to process 0
    MPI_Gather(rank < str_len ? &str[char_index] : NULL, 1, MPI_CHAR,
                str, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Print the result in process 0
    if (rank == 0) {
        printf("Original String: HeLLO\n");
        printf("Modified String: %s\n", str);
    }

    MPI_Finalize();
    return 0;
}

```
## Output 
```plaintext
Original String: ThisIsALongerString
Modified String: tHiSiSaLoNgErStRiNg
```
## Explanation
- The program initializes MPI environment, gets the total number of processes (`size`) and the rank of the current process (`rank`).

- A string `str` is defined with a maximum size of 100 characters, initialized with the value "HeLLO".

- The length of the string is determined using `strlen()` function.

- Each process calculates the character index to toggle based on its rank. This is done by taking the rank modulo the length of the string.

- Each process then toggles the character at its determined index. If the character is lowercase, it is converted to uppercase, and vice versa.

- Processes with ranks less than the length of the string participate in the toggling operation.

- The modified characters are gathered to process 0 using `MPI_Gather()`. Only the modified characters from processes with ranks less than the length of the string are gathered.

- Process 0 prints the original string and the modified string after gathering all the modifications.

- Finally, MPI environment is finalized using `MPI_Finalize()`.
--- 
# Additional Questions
### Q1.  1. Write a program in MPI to reverse the digits of the following integer array of size 9 with 9 processes. Initialize the 
### Input array to the following values.
Input array : `18, 523, 301, 1234, 2, 14, 108, 150, 1928`
Output array: `81, 325, 103, 4321, 2, 41, 801, 51, 8291`
```c
#include <stdio.h>
#include <mpi.h>

#define ARRAY_SIZE 9

int reverseDigits(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != ARRAY_SIZE) {
        if (rank == 0) {
            fprintf(stderr, "Please run the program with exactly 9 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int inputArray[ARRAY_SIZE] = { 18, 523, 301, 1234, 2, 14, 108, 150, 1928 };
    int outputArray[ARRAY_SIZE];
    int gatheredArray[ARRAY_SIZE];

    // Scatter the input array among processes
    MPI_Scatter(inputArray, 1, MPI_INT, &outputArray[rank], 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Reverse the digits
    outputArray[rank] = reverseDigits(outputArray[rank]);

    // Gather the reversed array using a separate buffer
    MPI_Gather(&outputArray[rank], 1, MPI_INT, gatheredArray, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the result
    if (rank == 0) {
        printf("Input array : ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", inputArray[i]);
        }
        printf("\nOutput array: ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", gatheredArray[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
```
### Output
```bash
C:\Users\Kartabya\source\repos\Week06-Aditional\x64\Debug>mpiexec -n 9 Week06-Aditional.exe
Input array : 18 523 301 1234 2 14 108 150 1928
Output array: 81 325 103 4321 2 41 801 51 8291
```
## Explanation
- The program begins by initializing MPI environment, obtaining the rank and size of the MPI communicator `MPI_COMM_WORLD`.

- It checks if the number of processes is exactly equal to the size of the input array (which is 9 in this case). If not, it displays an error message and exits.

- The input array is defined with the given values: `{ 18, 523, 301, 1234, 2, 14, 108, 150, 1928 }`.

- Three arrays are declared: `inputArray` to store the initial input values, `outputArray` to store the reversed values locally on each process, and `gatheredArray` to store the reversed values after gathering them from all processes.

- The input array is scattered among all processes using `MPI_Scatter()`. Each process receives one element of the input array.

- Each process then reverses the digits of the received element using the `reverseDigits()` function.

- The reversed values are gathered into the `gatheredArray` using `MPI_Gather()`.

- Process 0 prints both the input and output arrays once all processes have finished their computation.

- Finally, MPI environment is finalized using `MPI_Finalize()`.
---
### Q2 : Write a MPI program to find the prime numbers between 1 and 100 using 2 processes.
```c
#include <stdio.h>
#include <stdbool.h>
#include <mpi.h>

#define RANGE_START 1
#define RANGE_END 100

bool isPrime(int num) {
    if (num < 2) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            fprintf(stderr, "Please run the program with exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int start, end;
    int primesInRange = 0;

    if (rank == 0) {
        // Process 0 will check for primes in the first half of the range
        start = RANGE_START;
        end = RANGE_END / 2;
    }
    else {
        // Process 1 will check for primes in the second half of the range
        start = RANGE_END / 2 + 1;
        end = RANGE_END;
    }

    // Each process checks for prime numbers in its assigned range
    for (int num = start; num <= end; num++) {
        if (isPrime(num)) {
            primesInRange++;
        }
    }

    // Process 0 receives the count of primes from Process 1 and adds them
    if (rank == 0) {
        int receivedPrimes;
        MPI_Recv(&receivedPrimes, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        primesInRange += receivedPrimes;

        printf("Prime numbers between %d and %d: %d\n", RANGE_START, RANGE_END, primesInRange);
    }
    else {
        // Process 1 sends its count of primes to Process 0
        MPI_Send(&primesInRange, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
```
### Output
```bash
C:\Users\Kartabya\source\repos\Week06-Aditional\x64\Debug>mpiexec -n 2 Week06-Aditional.exe
Prime numbers between 1 and 100: 25
```
## Explanation 
- The program begins by initializing MPI environment, obtaining the rank and size of the MPI communicator `MPI_COMM_WORLD`.

- It checks if the number of processes is exactly equal to 2. If not, it displays an error message and exits.

- The `isPrime()` function checks whether a given number is prime or not. It returns true if the number is prime, otherwise false.

- Process 0 and Process 1 are assigned different ranges to search for prime numbers. Process 0 checks the first half of the range (1 to 50), and Process 1 checks the second half of the range (51 to 100).

- Each process counts the number of prime numbers in its assigned range.

- Process 1 sends its count of primes to Process 0 using `MPI_Send()`, while Process 0 receives the count from Process 1 using `MPI_Recv()`.

- Process 0 adds the received count of primes to its own count and prints the total number of primes found in the range.

- Finally, MPI environment is finalized using `MPI_Finalize()`.
---

