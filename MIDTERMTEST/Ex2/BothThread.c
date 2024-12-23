//Tran Vu Hong Phuc - 21ES - Exercise 2
//Library use for this code:
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
//Define the file pathname. Use this to reduce the time i need to code for input after again
#define FILENAME "writefile.txt"
typedef struct {
    char information[256]; //Define a buffer to store the information. In this case i use 256
    int thread_id; //Identify a unique identifier of thread
} thread_args_t;
// Mutex to manage resource sharing among threads
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//Function to write data to a file
void write_data(thread_args_t *thr) {
    //// Lock the mutex to ensure only one thread accesses this section at a time
    pthread_mutex_lock(&mutex);

    // Write into file
    FILE *file = fopen(FILENAME, "a");

    if (file == NULL) {
        printf("Failed to open file for writing\n");
        pthread_mutex_unlock(&mutex);
        exit(EXIT_FAILURE);
    }
    // Write information to the file
    if (fprintf(file, "Thread %d: %s\n", thr->thread_id, thr->information) < 0) {
        printf("Failed to write data to file\n");
    } else {
        printf("Thread %d wrote to file successfully\n", thr->thread_id);
    }
    fclose(file);
    // Unlock mutex
    pthread_mutex_unlock(&mutex);
}
//Function to handle thread1, write to file
static void *thread_1(void *args) {
    thread_args_t *thr = (thread_args_t *)args; // Allow thread to know its thread_id and parameters
    sleep(1);

    for (int i = 0; i < 5; i++) {
        snprintf(thr->information, sizeof(thr->information), "Data from iteration %d", i + 1);
        write_data(thr); // Pass the pointer to the structure
        sleep(1); // Simulate some work
    }
    pthread_exit(NULL);
}
//Function to handle thread2, write to file
static void *thread_2(void *args) {
    thread_args_t *thr = (thread_args_t *)args; // Allow thread to know its thread_id and parameters
    sleep(1);

    for (int i = 0; i < 5; i++) {
        snprintf(thr->information, sizeof(thr->information), "Data from iteration %d", i + 1);
        write_data(thr); // Pass the pointer to the structure
        sleep(1); // Simulate some work
    }
    pthread_exit(NULL);
}
// Function to read and print the contents of the file
void print_file_content() {
    // Open the file in read mode
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading\n");
        return; // Return if file can't be opened
    }
    // Buffer to store each line read from the file
    char line[256];
    printf("File Contents:\n");
    // Loop to read each line from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        // Print each line read from the file
        printf("%s", line);
    }
    // Close the file after reading
    fclose(file);
}
//Main function to create thread identifier, and control both thread static void*
int main(int argc, const char *argv[]) {
    int ret;
    thread_args_t thr1, thr2; // Two thread argument structures
    pthread_t thread_id1, thread_id2; //Thread ID of 2 threads
    thr1.thread_id = 1; // ID for the first thread
    thr2.thread_id = 2; // ID for the second thread
    // Mutex initialization
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1; //Return an error if mutex initialization fails
    }
    // Create the first thread (thr1)
    if ((ret = pthread_create(&thread_id1, NULL, &thread_1, &thr1)) != 0) {
        printf("pthread_create() error %d\n", ret); //Check the code thread1 create fails,
        return -1;
    }
    // Create the second thread (thr2)
    if ((ret = pthread_create(&thread_id2, NULL, &thread_2, &thr2)) != 0) {
        printf("pthread_create() error %d\n", ret); //Check the code thread2 create fails
        return -1;
    }
    // Wait for both threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    // Print the file contents
    print_file_content();

    return 0;
}
