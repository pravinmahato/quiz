#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

// Shared resource
int shared_data = 0;

// Synchronization variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t wrt;
int read_count = 0;

// Function to simulate a reader (With Synchronization)
void* reader(void* arg) {
    int id = *((int*)arg);

    // Entry Section
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt); // First reader blocks writers
    }
    pthread_mutex_unlock(&mutex);

    // Critical Section (Reading data)
    cout << "[With Sync] Reader " << id << " reads value: " << shared_data << endl;
    sleep(1); // Simulate reading time

    // Exit Section
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt); // Last reader unlocks writer
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Function to simulate a writer (With Synchronization)
void* writer(void* arg) {
    int id = *((int*)arg);

    // Entry Section
    sem_wait(&wrt); // Block other writers and readers

    // Critical Section (Writing data)
    shared_data++;
    cout << "[With Sync] Writer " << id << " updates value to: " << shared_data << endl;
    sleep(1); // Simulate writing time

    // Exit Section
    sem_post(&wrt); // Allow others to access

    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    // Initialize semaphore
    sem_init(&wrt, 0, 1);

    cout << "\n===== Running With Synchronization =====\n";

    // Create reader threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}
