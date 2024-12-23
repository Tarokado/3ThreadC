//Tran Vu Hong Phuc - 21ES - 

//Declare library for this exercise
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

/*Define the memory buffer. I use the buffer to store data(message), which i use to transfer data between the client and sever*/
#define SHMSIZE 2000

// Define the shared memory structure about message and waiting for client message
/* the data model Memory that both the client and server processes can access and modify through a shared memory segment*/
struct Memory {
    int ready; //Create signal to indicate message read(1 if ready, 0 if not)
    char message[SHMSIZE]; //BUffer size for store message of SHMSIZE, specifies the max size of the buffer
    /*In this case the client process write messages to this buffer, and the sever reads them*/
};

int main() {
    //ftok to generate unique key
    /*Using ftok(file to key) , takes a pathname to an existing file and a project identifier (an integer). Generates a unique key based on these inputs.
    Using a file that remains the same (like "shmfile") ensures that the key generated will be consistent between different executions of the same program or between different processes accessing the shared memory.
    shmfile: This is a path to an existing file on the filesystem. It does not have to be a specific file, but it must exist*/
    key_t key = ftok("shmfile", 65);

    //shmget returns an identifier in shmid
    /*Creates new shared memory segment or accesses an existing one based on the provided key
    struct Memory: specifies the size of the shared memory segment to be allocated or accessed. The struct hold the message and the ready flag for 1 and 0*/
    int shmid = shmget(key, sizeof(struct Memory), 0666);

    //shmat to attach to shared memory
    struct Memory *shared_data = (struct Memory *) shmat(shmid, NULL, 0);

    //Prompt the input from keyboard and send it to sever
    printf("Client connected. Enter a message (x to quit):\n");
    //Infinite loop to continually accept message 
    while (1) {
        //Prompt the user input
        printf("> ");
        //Read input from user and store it in shared memory message buffer
        fgets(shared_data->message, SHMSIZE, stdin);
        //The flag read is set to 1 , indicating that the message is ready to read
        shared_data->ready = 1;

        //The if statement for for user entered "x" to quit the terminal
        if (strncmp(shared_data->message, "x", 1) == 0) {
            break;
        }
    }

    // Detach from shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { //Remove shared memory segment
        perror("shmctl"); //Print error message
        exit(1); //Exit the program
    }
    return 0; //Return 0 when successful done program
}