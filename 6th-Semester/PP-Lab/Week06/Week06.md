# Not Final
#Q1 . Write a simple MPI program to find out pow (x, rank) for all the processes where 'x' is the
integer constant and 'rank' is the rank of the process.
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
==========================================================================
#Q2. Write a program in MPI where even ranked process prints "Hello" and odd ranked process
prints "World".
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

===================================================================================
#Q3. Write a program in MPI to simulate simple calculator. Perform each operation using
different process in parallel.
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

#Q4. Write a program in MPI to toggle the character of a given string indexed by the rank of the
process. Hint: Suppose the string is HeLLO and there are 5 processes, then process 0
toggle 'H' to 'h', process 1 toggle 'e' to 'E' and so on.
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char input_string[] = "HeLLO";

    // Calculate the portion of the string for each process
    int input_length = strlen(input_string);
    int local_string_size = input_length / world_size;
    char* local_string = (char*)malloc(local_string_size + 1);

    // Check if the input string length is sufficient for the number of processes
    if (input_length < world_size) {
        fprintf(stderr, "Error: String length is less than the number of processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Scatter(input_string, local_string_size, MPI_CHAR, local_string, local_string_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    local_string[local_string_size] = '\0'; // Null-terminate the local string

    // Toggle the character based on rank
    if (world_rank % 2 == 0) {
        for (size_t i = 0; i < strlen(local_string); ++i) {
            if (local_string[i] >= 'a' && local_string[i] <= 'z') {
                local_string[i] = local_string[i] - 'a' + 'A'; // Toggle lowercase to uppercase
            }
        }
    }
    else {
        for (size_t i = 0; i < strlen(local_string); ++i) {
            if (local_string[i] >= 'A' && local_string[i] <= 'Z') {
                local_string[i] = local_string[i] - 'A' + 'a'; // Toggle uppercase to lowercase
            }
        }
    }

    // Gather the modified strings at process 0
    char* gathered_string = NULL;
    if (world_rank == 0) {
        gathered_string = (char*)malloc(input_length + 1);
    }

    MPI_Gather(local_string, local_string_size, MPI_CHAR, gathered_string, local_string_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Null-terminate the gathered string
    if (world_rank == 0) {
        gathered_string[input_length] = '\0';
        printf("Original String: %s\n", input_string);
        printf("Modified String: %s\n", gathered_string);

        free(gathered_string); // Don't forget to free the allocated memory
    }

    free(local_string); // Don't forget to free the allocated memory
    MPI_Finalize();
    return 0;
}
```
## Output 
```plaintext
PS C:\Users\mca\source\repos\210968244\x64\Debug> mpiexec -n 5 210968244.exe
Original String: HeLLO
Modified String: HeLlO
```




