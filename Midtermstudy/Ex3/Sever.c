//Tran Vu Hong Phuc - 21ES 
//Code for sever 
//Declare library for this exercise
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

//Define the shared memory segment
#define SHMSIZE 2000

// Define the shared memory structure about message and waiting for client message
struct Memory {
    int ready; //Create signal to indicate message read(1 if ready, 0 if not)
    char message[SHMSIZE]; //BUffer size for store message
};

int main() {
    //Generate a unique key using the file "shmfile" and an identifier (65)
    /*Using ftok(file to key) , takes a pathname to an existing file and a project identifier (an integer). Generates a unique key based on these inputs.
    Using a file that remains the same (like "shmfile") ensures that the key generated will be consistent between different executions of the same program or between different processes accessing the shared memory.
    shmfile: This is a path to an existing file on the filesystem. It does not have to be a specific file, but it must exist*/
    key_t key = ftok("shmfile", 65);

    //shmget returns an identifier in shmid
    /*Creates new shared memory segment or accesses an existing one based on the provided key
    struct Memory: specifies the size of the shared memory segment to be allocated or accessed. The struct hold the message and the ready flag for 1 and 0*/
    int shmid = shmget(key, sizeof(struct Memory), 0666|IPC_CREAT);

    //shmat to attach to shared memory
    struct Memory *shared_data = (struct Memory *) shmat(shmid, NULL, 0);
    
    //Print a message indicating that the server is ready and waiting for client messages
    printf("SEVER READY, waiting message from client: \n");

    // Wait for a message
    while (1) {
        if (shared_data->ready) {
            printf("Received message from client: %s\n", shared_data->message);
            shared_data->ready = 0;  // Reset ready flag
        }
        sleep(1);  // Simulate waiting
    }

    //Detach from shared memory
    if (shmdt(shared_data) == -1) {
        perror("shmdt");
        exit(1);
    }
    //Destroy the shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    return 0;
}
