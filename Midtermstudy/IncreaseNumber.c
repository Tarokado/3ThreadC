//Declare library used for this Exercise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//Define LIMIT of word is 1000, when reach 1000 the code is finished
#define LIMIT 1000

/*In this exercises. I'm want to combine mutex and condition variables. I want to combine them because i want to prevent race conditions 
So the mutexes protect shared resources, and condition variables enable waiting for specific events.*/
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; //Declare the mutex
int global_value = 0; //Using shared variables
pthread_cond_t cond;
int checker= 0; // 0: thread for even, 1: thread for odd

//Define structure named thread_args_t
typedef struct {
    int thread_id; //An integer representing the identifier of a thread
    int checker; //Track the number of operations, status, or other relevant information of a thread => Pass multiple to a thread function 
} thread_args_t;

//Declare odd thread to increase data increment 
static void* increase_odd(void *args){
    thread_args_t *thr = (thread_args_t *)args; //Allow thread to know its thread_id and any other parameters passed
    sleep(1);

    while(global_value < LIMIT){
        pthread_mutex_lock(&lock); //Ensure that thread increase odd can access the critical section
        while(checker!= 1){ //odd thread proceed when checker== 1, so this is odd thread's turn 
            pthread_cond_wait(&cond,&lock); //The thread will wait and relesease the mutex receives signal from even thread
        }
        if(global_value % 2 == 0 && global_value < LIMIT){
            global_value++;
            printf("Thread %d (Odd) incremented value to: %d\n", thr -> thread_id,global_value);
        }
        // Change checkerto even (0)
        sleep(1);
        checker= 0; //After increase, thread set checker= 0 => even thread's turn 
        pthread_cond_signal(&cond); //send the signal to wake up thread even, which was sleeping in pthread_cond_wait(&cond,&lock);
        pthread_mutex_unlock(&lock); //allowing the even thread to 
    }

    pthread_exit(NULL);
}

//Declare even thread to increase data increment 
static void* increase_even(void *args){
    thread_args_t *thr = (thread_args_t *)args; //Allow thread to know its thread_id and any other parameters passed
    sleep(1);

    while(global_value < LIMIT){
        pthread_mutex_lock(&lock); //Ensure that thread increase odd can access the critical section
        while(checker!= 0){ //odd thread proceed when checker== 1, so this is odd thread's turn 
            pthread_cond_wait(&cond,&lock); //The thread will wait and relesease the mutex receives signal from even thread
        }
        if(global_value % 2 == 1 && global_value < LIMIT){
            global_value++;
            printf("Thread %d (Even) incremented value to: %d\n", thr -> thread_id,global_value);
        }
        // Change checkerto even (0)
        sleep(1);
        checker= 1; //After increase, thread set checker= 0 => odd thread's turn 
        pthread_cond_signal(&cond); //send the signal to wake up thread even, which was sleeping in pthread_cond_wait(&cond,&lock);
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}
int main(int argc , char const *argv[]){
    int ret;
    thread_args_t thr1, thr2;
    pthread_t thread_id1, thread_id2;
    // Initialize thread_args for thread 1 (Odd)
    memset(&thr1, 0, sizeof(thread_args_t)); // Zero out the struct
    thr1.thread_id = 1;  // Set thread_id for odd thread

    // Initialize thread_args for thread 2 (Even)
    memset(&thr2, 0, sizeof(thread_args_t)); // Zero out the struct
    thr2.thread_id = 2;  // Set thread_id for even thread

    // Create the first thread (increase_odd)
    ret = pthread_create(&thread_id1, NULL, &increase_odd, &thr1);
    if (ret != 0) {
        printf("pthread_create() error for thread 1, error number=%d\n", ret);
        return -1;
    }

    // Create the second thread (handle_th2)
    ret = pthread_create(&thread_id2, NULL, &increase_even, &thr2);
    if (ret != 0) {
        printf("pthread_create() error for thread 2, error number=%d\n", ret);
        return -1;
    }
    // Wait for the threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;

}















