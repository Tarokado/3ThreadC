#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
//Define Max value of data and file path .txt
#define MAX 256
#define FILENAME "thongtinsinhvien.txt"
// Structure to hold student data

pthread_t threadid1, threadid2, threadid3;

typedef struct {
    char name[MAX];
    char dob[MAX];
    char hometown[MAX];
} Student;
// Shared resources
Student student;
pthread_mutex_t mutex;
pthread_cond_t cond_input, cond_write, cond_read;
int ready_to_write = 0;
int ready_to_read = 0;

// Function to get student data from user
void read_input(const char *prompt, char *field) {
    printf("%s", prompt);
    if (fgets(field, MAX, stdin) == NULL) {
        perror("Error reading input");
    }
    field[strcspn(field, "\n")] = '\0';
}
// keyboard input
void get_student_data(Student *student) {
    read_input("Enter student name: ", student->name);
    read_input("Enter date of birth: ", student->dob);
    read_input("Enter hometown: ", student->hometown);
}
// Function to write student data to a file
void write_data(Student *student) {
    FILE *file = fopen(FILENAME, "a");
    /*if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    } */
    // Write student data to file
    fprintf(file, "Name: %s\nDOB: %s\nHometown: %s\n",student->name, student->dob, student->hometown);
    fclose(file);
}
// Function to read student data from a file
void read_data() {
    char buffer[MAX];
    FILE *file = fopen(FILENAME, "r");
    /*if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    } */
    // Print the entire file contents (all student records)
    printf("\nStudent Inform\n");
    while (fgets(buffer, MAX, file) != NULL) {
        printf("%s", buffer);
    }
    printf("End of Input\n");
    fclose(file);
}
//Thread1 input
void *input_thread(void *args) {
    while (1) {
        pthread_mutex_lock(&mutex);
        get_student_data(&student); // Get student data
        // Notify write thread
        ready_to_write = 1;
        pthread_cond_signal(&cond_write);
        // Wait for reading thread to finish before allowing more input
        pthread_cond_wait(&cond_input, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
//Thread2 write
void *write_thread(void *args) {
    while (1) {
        pthread_mutex_lock(&mutex);
        // Wait for input thread to provide student data
        while (!ready_to_write){
            pthread_cond_wait(&cond_write, &mutex);
        }
        // Write student data
        write_data(&student);
        // Notify read thread
        ready_to_read = 1;
        pthread_cond_signal(&cond_read);
        ready_to_write = 0; // Reset ready to write flag
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
//Thread3 read
void *read_thread(void *args) {
    while (1) {
        pthread_mutex_lock(&mutex);
        // Wait for write thread to finish writing
        while (!ready_to_read){
            pthread_cond_wait(&cond_read, &mutex);
        }
        // Read student data
        read_data();
        // Notify input thread to take new input
        ready_to_read = 0;
        pthread_cond_signal(&cond_input);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main() {
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_input, NULL);
    pthread_cond_init(&cond_write, NULL);
    pthread_cond_init(&cond_read, NULL);
    //Create function
    pthread_create(&threadid1, NULL, input_thread, NULL);
    pthread_create(&threadid2, NULL, write_thread, NULL);
    pthread_create(&threadid3, NULL, read_thread, NULL);
    // Wait for threads to finish
    pthread_join(threadid1, NULL);
    pthread_join(threadid2, NULL);
    pthread_join(threadid3, NULL);
    //Destroy all mutex and cond
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_input);
    pthread_cond_destroy(&cond_write);
    pthread_cond_destroy(&cond_read);
    return 0;
}
