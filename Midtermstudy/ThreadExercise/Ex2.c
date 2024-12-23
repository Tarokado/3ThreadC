#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "writefile.txt"

typedef struct {
    char information[256];
    int thread_id;
} thread_args_t;

pthread_mutex_t mutex;

void write_data(thread_args_t *thr) {
    // Lock mutex
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
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading\n");
        return;
    }

    char line[256];
    printf("File Contents:\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}

int main(int argc, const char *argv[]) {
    int ret;
    thread_args_t thr1, thr2; // Two thread argument structures
    pthread_t thread_id1, thread_id2;
    thr1.thread_id = 1; // ID for the first thread
    thr2.thread_id = 2; // ID for the second thread

    // Mutex initialization
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create the first thread (thr1)
    if ((ret = pthread_create(&thread_id1, NULL, &thread_1, &thr1)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    // Create the second thread (thr2)
    if ((ret = pthread_create(&thread_id2, NULL, &thread_2, &thr2)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
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
