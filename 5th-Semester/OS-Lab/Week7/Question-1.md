## 1. Write a C program for the bounded buffer producer-consumer problem using semaphores.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h> // For sleep

#define BUFFER_SIZE 5

sem_t empty, full, mutex; // Semaphores to manage buffer access and slots
int buffer[BUFFER_SIZE]; // The shared buffer
int in = 0, out = 0; // Pointers to track the buffer positions
bool running = true; // A flag to signal when to terminate threads

// Producer thread function
void *producer(void *arg) {
    int item = 1;
    while (running) {
        // Produce an item
        item = rand() % 100;

        // Wait for an empty slot in the buffer
        sem_wait(&empty);

        // Acquire the mutex to access the buffer
        sem_wait(&mutex);

        // Add the item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        // Release the mutex to allow other threads access
        sem_post(&mutex);

        // Signal that a new item is in the buffer
        sem_post(&full);

        printf("Produced: %d\n", item);
    }
    pthread_exit(NULL); // Exit the thread when done
}

// Consumer thread function
void *consumer(void *arg) {
    int item;
    while (running) {
        // Wait for a full slot in the buffer
        sem_wait(&full);

        // Acquire the mutex to access the buffer
        sem_wait(&mutex);

        // Remove an item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        // Release the mutex to allow other threads access
        sem_post(&mutex);

        // Signal that a slot is empty
        sem_post(&empty);

        printf("Consumed: %d\n", item);
    }
    pthread_exit(NULL); // Exit the thread when done
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // 'empty' initially has BUFFER_SIZE slots available
    sem_init(&full, 0, 0); // 'full' initially has no slots filled
    sem_init(&mutex, 0, 1); // 'mutex' initially is available for the first thread

    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Run the threads for a specific time (e.g., 10 seconds)
    sleep(10);
    running = false; // Set the termination signal

    // Wait for the threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up and destroy the semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
```
## Output
![Alt text](image.png)

### Explanation 

#### Bounded Buffer Producer-Consumer Problem

##### Problem Description
The bounded buffer producer-consumer problem models a situation where multiple producer threads generate data, place it into a shared buffer, and multiple consumer threads retrieve and process this data. The challenge is to ensure that the producers don't overflow the buffer (exceed its capacity) and that consumers don't underflow it (try to consume when the buffer is empty).

##### Synchronization Elements
This code implements the solution using semaphores:

- **empty**: Represents the number of empty slots in the buffer.
- **full**: Represents the number of slots that contain data in the buffer.
- **mutex**: Ensures mutual exclusion when accessing the buffer.

##### Implementation Overview
- The code defines two types of threads, one for the producer and one for the consumer.
- The producer generates data and adds it to the buffer, making sure it doesn't exceed the buffer's capacity.
- The consumer retrieves and processes data from the buffer, avoiding buffer underflow.
- The threads are synchronized using semaphores to coordinate access to the shared buffer.

##### Usage
- Compile the code, for example: `gcc bounded_buffer.c -o bounded_buffer -lpthread`
- Run the executable: `./bounded_buffer`
- The program will create producer and consumer threads that run concurrently.
- Threads will run for a specified duration (e.g., 10 seconds) and then exit gracefully.

##### Customization
You can customize this code by changing the `BUFFER_SIZE` and the data generated by the producer to fit your requirements.

##### Cleanup
The program cleans up and destroys the semaphores when it finishes execution.

---

This README provides an overview of a practical solution to the bounded buffer producer-consumer problem using semaphores in C. It ensures efficient coordination between producers and consumers while avoiding buffer overflows and underflows.

