//Declare library for this code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
// Define MAX_VALUE as 1000; when it reaches 1000, the program finishes
#define MAX_VALUE 1000
//Define mutex lock
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// Define a shared variable that will be accessed and modified by thread1 and thread2
int shared_value = 0; // Shared variable

// Define a structure to hold arguments passed to threads
typedef struct {
    int thread_id; // Identifier for the thread
} thread_args_t;

//First thread for increase odd number. For example increase ike 1 3 5 7 
static void* ODD(void *args) {
    //Passed argument to the right correct type of (thread_args_t)
    thread_args_t *thr = (thread_args_t *)args; //Allow thread for its own ID
    sleep(1);

    /*While loop to check for the shared_value reach the number ODD i want like 1 3 5 7*/
    while (shared_value < MAX_VALUE) {
        /*Lock the mutex, ensure that thread 1 only access the odd number. Thread 2 can't access to control value*/
        pthread_mutex_lock(&lock);
        // Check if the current shared value is even by the divide it for 2
        if (shared_value % 2 == 0) {
            //Increament the shared value to make it odd
            shared_value++;
            //Print the value to the terminal with the threadID, and the value i want to show for first thread
            printf("Thread %d increase value to: %d\n", thr->thread_id, shared_value);
        }
        // Unlock the mutex to allow other threads to access shared_value
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    //End the thread
    pthread_exit(NULL); 
}
//Second thread for increase even number. For example increase like 2 4 6 8 
static void* EVEN(void *args) {
    //Passed argument to the right correct type of (thread_args_t)
    thread_args_t *thr = (thread_args_t *)args; // Allow thread to know its thread_id
    sleep(1);

    /*While loop to check for the shared_value reach the number ODD i want like 2 4 6 8*/
    while (shared_value < MAX_VALUE) {
        /*Lock the mutex, ensure that thread 1 only access the odd number. Thread 1 can't access to control value*/
        pthread_mutex_lock(&lock);
        // Check if the current shared value is odd by the divide it for 2 in condition not equal
        if (shared_value % 2 != 0) {
            //Increament the shared value to make it odd
            shared_value++;
            //Print the value to the terminal with the threadID, and the value i want to show for second thread
            printf("Thread %d increase value to: %d\n", thr->thread_id, shared_value);
        }
        // Unlock the mutex to allow other threads to access shared_value
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    // End the thread
    pthread_exit(NULL); 
}
//In this exercise, i want to use 2 thread and mutex to increase the share_value from 1 to 1000 using mutex, increase 1 unit until reach 1000
int main(int argc, const char *argv[]) {
    int ret;
    thread_args_t thr1, thr2; // Two thread argument structures
    pthread_t thread_id1, thread_id2;// Thread identifiers for the two threads
    thr1.thread_id = 1; // ID for odd thread, declare ID like first thread is 1 , second thread is 2
    thr2.thread_id = 2; // ID for even thread
    //Mutex initialize access to share variables
    if (pthread_mutex_init(&lock, NULL) != 0) {
        /// Mutex initialization fails, print an error message
        printf("Mutex initialization failed.\n");
        return 1;
    }

    /*Create the first thread to execute the first thread
    Pass the ID and thread arguments for the first thread*/
    if ((ret = pthread_create(&thread_id1, NULL, &ODD, &thr1)) != 0) {
        //Thread creation fails, print an error message with the error code
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    /*Create the first thread to execute the second thread
    Pass the ID and thread arguments for the second thread*/
    if ((ret = pthread_create(&thread_id1, NULL, &EVEN, &thr2)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    // Wait for the first thread (ODD) to finish execution
    pthread_join(thread_id1, NULL);
    // Wait for the second thread (EVEN) to finish execution
    pthread_join(thread_id2, NULL);

    // Destroy the mutex as it is no longer needed
    pthread_mutex_destroy(&lock);
    return 0;
}
