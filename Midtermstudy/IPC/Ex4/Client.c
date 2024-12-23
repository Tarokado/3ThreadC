//Tran Vu Hong Phuc - 21ES - Exercise client socket TCP
//Define library use for this code:
#include <arpa/inet.h> 
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> 
#include <sys/socket.h>
#include <unistd.h> 

#define MAX_VALUE 256 //Define the maximum size of the message buffer
#define PORT 8080 //Define the PORT use for sever
#define StructAdd struct sockaddr

//Function to communication with sever 
void func(int sockfd)
{
    char buff[MAX_VALUE];//Buffer to store the message
    int n; //Variables to count the number of character

    //Infinite loop to communication with sever
    for (;;) {
        bzero(buff, sizeof(buff)); //Clear the buffer before taking new input
        printf("Enter the messages: "); //Send the messages to Sever

        //User input interact and store in the buffer
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        
        //Send the message stored in the buffer to the sever
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));//Clear the buffer
        
        //Read the sever's response
        read(sockfd, buff, sizeof(buff));
        printf("From Server: %s", buff); //Print the sever response
        //Terminate the chat
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit\n");
            break;
        }
    }
}
//Main function to initialize the client
int main()
{
    int sockfd; //Socket file descriptor 
    struct sockaddr_in servaddr; //Structure to hold sever address information

    //Create socket for client using sockfd TCP sock_stream and using IPv4(AF_NET)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Failed to create socket\n"); //Print error message if not successfull create
        exit(0);
    }
    else{
        printf("Socket created successfully\n"); //This line print successful create socket TCP for communication with sever
    }
    // Clear the server address structure before assigning values
    bzero(&servaddr, sizeof(servaddr));

    // Assign IP and port to the server address structure
    servaddr.sin_family = AF_INET; //Set address for IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set sever IP address for local host
    servaddr.sin_port = htons(PORT); //Set sever PORT number

    //Connect client socket to sever socket using sever address structure
    if (connect(sockfd, (StructAdd*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connecting to the Sever\n");
        exit(0);
    }
    else{
        printf("Connected to sever using socket TCP finished\n");
    }
    // Call the communication function to start exchanging messages with the server
    func(sockfd);
    // Close the client socket after finishing communication
    close(sockfd);
}