## 1. Write a MPI program using synchronous send. The sender process sends a word to the receiver. The second process receives the word, toggles each letter of the word and sends it back to the first process. Both processes use synchronous send operations.

```cpp
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

void toggle_case(char* word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (isupper(word[i]))
            word[i] = tolower(word[i]);
        else if (islower(word[i]))
            word[i] = toupper(word[i]);
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    const int tag = 0;
    const int root = 0;
    
    if (rank == root) {
        // Sender process
        const char* word = "Hello";
        printf("Process %d sends word: %s\n", rank, word);
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
        
        // Receive the toggled word back from process 1
        char received_word[100];
        MPI_Recv(received_word, 100, MPI_CHAR, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received toggled word: %s\n", rank, received_word);
        
    } else if (rank == 1) {
        // Receiver process
        char word[100];
        MPI_Recv(word, 100, MPI_CHAR, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received word: %s\n", rank, word);
        
        // Toggle the case of each letter in the word
        toggle_case(word);
        
        // Send it back to the sender process
        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
```
## Output
```plaintext
C:\Users\suzen>cd C:\Users\suzen\source\repos\week7\Q1\x64\Debug

C:\Users\suzen\source\repos\week7\Q1\x64\Debug>mpiexec -n 2 Q1.exe
Process 1 received word: Hello
Process 0 sends word: Hello
Process 0 received toggled word: hELLO
```
---
## 2. Write a MPI program where the master process (process 0) sends a number to each of the slaves and the slave processes receive the number and prints it. Use standard send.

```cpp
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;
    if (world_rank == 0) {
        // Master process
        // Choose a number to send to all slave processes
        number = 777;  // You can change this number to any number you want to send

        // Use MPI_Send to send it to all the other processes
        for (int i = 1; i < world_size; i++) {
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master process sending number %d to process %d\n", number, i);
        }
    } else {
        // Slave processes
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Slave process %d received number %d from master process\n", world_rank, number);
    }

    MPI_Finalize();
    return 0;
}
```
## Output
```plaintext
C:\Users\suzen\source\repos\week7\Q1\x64\Debug>cd C:\Users\suzen\source\repos\week7\Q2\x64\Debug\

C:\Users\suzen\source\repos\week7\Q2\x64\Debug>mpiexec -n 4 Q2.exe
Slave process 3 received number 777 from master process
Slave process 2 received number 777 from master process
Slave process 1 received number 777 from master process
Master process sending number 777 to process 1
Master process sending number 777 to process 2
Master process sending number 777 to process 3
```
---
# 3. Write a MPI program to read N elements of the array in the root process (process 0) where N is equal to the total number of process. The root process sends one value to each of the slaves. Let even ranked process finds square of the received element and odd ranked process finds cube of received element. Use Buffered send.

```cpp
```
## Output
```plaintext
```
---
# 4. Write a MPI program to read an integer value in the root process. Root process sends this value to Process1, Process1 sends this value to Process2 and so on. Last process sends the value back to root process. When sending the value each process will first increment the received value by one. Write the program using point to point communication routines. 

```cpp
```
## Output
```plaintext
```
---
# 5. Write a MPI program to read N elements of an array in the master process. Let N processes including master process check the array values are prime or not.

```cpp
```
## Output
```plaintext
```
---
