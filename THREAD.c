#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
//Define file path .txt
#define FILENAME "thongtinsinhvien.txt"
// Structure to hold student data
typedef struct {
    char Name[256];
    char Date[256];
    char Home[256];
} Student;
// Shared resources
Student student;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;;
pthread_cond_t cond_input, cond_write, cond_read;
int re_write = 0;
int re_read = 0;
// Function to get student data from user
void read_input(const char *prompt, char *Stu) {
    printf("%s", prompt);
    if (fgets(Stu, 256, stdin) == NULL) {
        printf("Cant read input");
    }
    size_t len = strcspn(Stu, "\n");
    Stu[len] = '\0';
}
// keyboard input user data
void get_student_data(Student *stu) {
    printf("Enter name: ");
    scanf("%s", stu->Name);
    printf("Enter BirthDay: ");
    scanf("%s", stu->Date);
    printf("Enter Home: ");
    scanf("%s", stu->Home);
}
// Function to write student data to a file
void write_data(Student *student) {
    FILE *file = fopen(FILENAME, "a");
    
    if (file == NULL) {
        printf("Failed to open file for writing");
        exit(EXIT_FAILURE);
    } 
    // Write student data to file
    if (fprintf(file, "Name: %s\nBirthDay: %s\nHome: %s\n", student->Name, student->Date, student->Home) < 0) {
        printf("Failed to write data to file");
    }    
    fclose(file);
}
// Function to read student data from a file
void read_data() {
    char buffer[256];
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading");
        exit(EXIT_FAILURE);
    } 
    // Print the entire file contents (all student records)
    printf("\nStudent Inform\n");
    while (fgets(buffer, 256, file) != NULL) {
        printf("%s", buffer);
    }
    printf("End of Input\n");
    fclose(file);
}
//Thread1 input
static void *input_thread(void *args) {
    while(1){
        pthread_mutex_lock(&lock);
        get_student_data(&student); // Get student data
        // Notify write thread
        re_write = 1;
        pthread_cond_signal(&cond_write);
        // Wait for reading thread to finish before allowing more input
        pthread_cond_wait(&cond_input, &lock);
        sleep(5);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
//Thread2 write
static void *write_thread(void *args) {
    while(1){
        pthread_mutex_lock(&lock);
        // Wait for input thread to provide student data
        while (!re_write){
            pthread_cond_wait(&cond_write, &lock);
        }
        // Write student data
        write_data(&student);
        // Notify read thread
        re_read = 1;
        sleep(1);
        pthread_cond_signal(&cond_read);
        re_write = 0; // Reset ready to write flag
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
//Thread3 read
static void *read_thread(void *args) {
    while(1){
        pthread_mutex_lock(&lock);
        // Wait for write thread to finish writing
        while (!re_read){
            pthread_cond_wait(&cond_read, &lock);
        }
        // Read student data
        read_data();
        // Notify input thread to take new input
        re_read = 0;
        sleep(1);
        pthread_cond_signal(&cond_input);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main(int argc, char const *argv[]) {
    // Initialize mutex and condition variables
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("Mutex initialization failed.\n");
        return 1;
    }
    if (pthread_cond_init(&cond_input, NULL) != 0 ||
        pthread_cond_init(&cond_write, NULL) != 0 ||
        pthread_cond_init(&cond_read, NULL) != 0) {
        perror("Failed for conditional variables");
        exit(0);
    }
    pthread_t threadid1, threadid2, threadid3;
    // Create threads
    if (pthread_create(&threadid1, NULL, input_thread, NULL) != 0 ||
        pthread_create(&threadid2, NULL, write_thread, NULL) != 0 ||
        pthread_create(&threadid3, NULL, read_thread, NULL) != 0) {
        perror("Cant create thread");
        exit(EXIT_FAILURE);
    }
    // Wait for threads to finish
    pthread_join(threadid1, NULL);
    pthread_join(threadid2, NULL);
    pthread_join(threadid3, NULL);
    // Destroy all mutex and condition variables
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_input);
    pthread_cond_destroy(&cond_write);
    pthread_cond_destroy(&cond_read);
    return 0;
}
