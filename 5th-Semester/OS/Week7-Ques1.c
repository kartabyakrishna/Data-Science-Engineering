#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg) {
    int item = 1;
    while (1) {
        // Produce an item
        item = rand() % 100;
        
        // Wait for an empty slot in the buffer
        sem_wait(&empty);
        
        // Acquire the mutex
        sem_wait(&mutex);
        
        // Add item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        
        // Release the mutex
        sem_post(&mutex);
        
        // Signal that a new item is in the buffer
        sem_post(&full);
        
        printf("Produced: %d\n", item);
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        // Wait for a full slot in the buffer
        sem_wait(&full);
        
        // Acquire the mutex
        sem_wait(&mutex);
        
        // Remove item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        
        // Release the mutex
        sem_post(&mutex);
        
        // Signal that a slot is empty
        sem_post(&empty);
        
        printf("Consumed: %d\n", item);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}
