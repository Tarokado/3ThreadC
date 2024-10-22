#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define FILENAME "writefile.txt"

typedef struct{ 
    char information[256];
    int thread_id;
} thread_args_t;

thread_args_t thr;
pthread_mutex_t mutex;

void write_data(thread_args_t *thr) {
    //Lock mutex
    pthread_mutex_lock(&mutex);

    //Write into file
    FILE *file = fopen(FILENAME, "a");
    
    if (file == NULL) { 
        printf("Failed to open file for writing");
        pthread_mutex_unlock(&mutex);
        exit(EXIT_FAILURE);
    } 
    //Write information to .txt file
    if (fprintf(file, "%s \n") < 0) {
        printf("Failed to write data to file");
    
    }else{
        printf("Write to file successfully\n");
    }
    fclose(file);

    pthread_mutex_unlock(&mutex);
}

static void *thread_1(void *args){
    thread_args_t *thr = (thread_args_t *)args; //Allow thread to know its thread_id and any other parameters passed
    sleep(1);

    for (int i = 0; i < 5; i++) {
        snprintf(thr->information, sizeof(thr->information), "Data from thread %d, iteration %d", thr->thread_id, i + 1);
        write_data(thr); // Pass the pointer to the structure
        sleep(1); // Simulate some work
    }
    pthread_exit(NULL);
}
static void *thread_2(void *args){
    thread_args_t *thr = (thread_args_t *)args; //Allow thread to know its thread_id and any other parameters passed
    sleep(1);

    for (int i = 0; i < 5; i++) {
        snprintf(thr->information, sizeof(thr->information), "Data from thread %d, iteration %d", thr->thread_id, i + 1);
        write_data(thr); // Pass the pointer to the structure
        sleep(1); // Simulate some work
    }
    pthread_exit(NULL);
}
//In this exercise, i want to use 2 thread and mutex to increase the share_value from 1 to 1000 using mutex, increase 1 unit until reach 1000
int main(int argc, const char *argv[]) {
    int ret;
    thread_args_t thr1, thr2; // Two thread argument structures
    pthread_t thread_id1, thread_id2;
    thr1.thread_id = 1; // ID for odd thread, declare ID like first thread is 1 , second thread is 2
    thr2.thread_id = 2; // ID for even thread
    //Mutex initialize
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create the first thread (ODD), the second thread(increase even)
    if ((ret = pthread_create(&thread_id1, NULL, &thread_1, &thr1)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if ((ret = pthread_create(&thread_id1, NULL, &thread_2, &thr2)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    // Wait for both threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
