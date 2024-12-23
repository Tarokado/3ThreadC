#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
// Define MAX_VALUE as 1000; when it reaches 1000, the program finishes
#define MAX_VALUE 1000
pthread_mutex_t lock;
int shared_value = 1; // Shared variable

typedef struct {
    int thread_id;
} thread_args_t;
//First thread for increase odd number. For example increase ike 1 3 5 7 
static void* ODD(void *args) {
    thread_args_t *thr = (thread_args_t *)args; // Allow thread to know its thread_id
    sleep(1);

    while (shared_value < MAX_VALUE) {
        pthread_mutex_lock(&lock);
        if (shared_value % 2 != 0){
            shared_value++;
            printf("Thread %d increase value to: %d\n", thr->thread_id, shared_value);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    pthread_exit(NULL); // End the thread
}
//Second thread for increase even number. For example increase like 2 4 6 8 
static void* EVEN(void *args) {
    thread_args_t *thr = (thread_args_t *)args; // Allow thread to know its thread_id
    sleep(1);

    while (shared_value < MAX_VALUE) {
        pthread_mutex_lock(&lock);
        if (shared_value % 2 == 0) {
            shared_value++;
            printf("Thread %d increase value to: %d\n", thr->thread_id, shared_value);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    pthread_exit(NULL); // End the thread
}
//In this exercise, i want to use 2 thread and mutex to increase the share_value from 1 to 1000 using mutex, increase 1 unit until reach 1000
int main(int argc, const char *argv[]) {
    int ret;
    thread_args_t thr1, thr2; // Two thread argument structures
    pthread_t thread_id1, thread_id2;
    thr1.thread_id = 1; // ID for odd thread, declare ID like first thread is 1 , second thread is 2
    thr2.thread_id = 2; // ID for even thread
    //Mutex initialize
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create the first thread (ODD), the second thread(increase even)
    if ((ret = pthread_create(&thread_id1, NULL, &ODD, &thr1)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if ((ret = pthread_create(&thread_id1, NULL, &EVEN, &thr2)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    // Wait for both threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
