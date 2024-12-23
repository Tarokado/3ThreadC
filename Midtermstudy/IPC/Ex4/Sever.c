//Tran Vu Hong Phuc - 21ES - Exercise using socket
//Declare library using for this exercises
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()

#define MAX_VALUE 256 //Maximum size for the buffer value 
#define PORT 8080 //Define sever port number to communicate using socket TCP    
#define StructAdd struct sockaddr //define struct socket address 

//Function for chat between client and sever
void func(int connfd) 
{ 
    char buff[MAX_VALUE]; //Buffer to store messages 
    int n; 

    //Build inifinite loop to keep the chat open until receive "exit"
    for (;;) { 
        bzero(buff, MAX_VALUE); //Clear the buffer

        //Read message from client and store it in the buffer
        read(connfd, buff, sizeof(buff)); 
        
        //Print the received messages
        printf("From client: %s\t To client: ", buff); 

        //Clear the buffer to prepare it for the sever's response
        bzero(buff, MAX_VALUE); 
        n = 0; 
        //Get the server's response from the console input
        while ((buff[n++] = getchar()) != '\n') 
            ; //Read until a newline character is received

        //Send the server's response to the client
        write(connfd, buff, sizeof(buff)); 

        //Check if the server wants to exit
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
} 
//Main function to initialize the sever
int main() 
{ 
    int sockfd, connfd, len;  //File descriptors for the socket and connection
    struct sockaddr_in servaddr, cli; //Structure for sever and client addresses

    //Create a socket sockfd TCP sock_stream and using IPv4(AF_NET)
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("Socket creation failed...\n"); // Error message if socket creation fails
        exit(0); 
    } 

    else{
        printf("Socket successfully created..\n");  //Success message for socket creation
    }

    bzero(&servaddr, sizeof(servaddr)); //Clear the server address structure

    // Assign IP and port to the server address structure
    servaddr.sin_family = AF_INET; //Here is IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //Listen for all network interfaces
    servaddr.sin_port = htons(PORT); //Assign the sever port

    /*Bind the socket to the IP and port, Check for another code or program use this PORT like PID 
    when another still have this PID. We need to check this ID, and kill this ID
    For example use kill -9 <PID> To destroy this PID, and use for another code*/
    if ((bind(sockfd, (StructAdd*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("Bind socket got failed, please use(kill -9 <PID>) to destroy the signal\n"); //Print the message to help the user know this Sever can bind to PORT 8080
        exit(0); //Exit the program
    } 
    else{
        printf("Binded successfully\n"); //Success bind the socket 
    }
    //Start listening for client connections, with a maximum queue of 5 connections
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen got failed\n"); // Error message if listening fails
        exit(0); //Exit the program
    } 
    else{
        printf("Sever is listening\n");  //Success messages for listening
    }
    len = sizeof(cli); 

    //Accept an incoming connection request from a client
    connfd = accept(sockfd, (StructAdd*)&cli, &len);/*This line for incoming connection request on the sever socket. 
    IF a client attempts to connect to the sever, the sever will accept that connection request*/
    if (connfd < 0) {  
        printf("Acceptance failed\n");  //error message if accepting fails
        exit(0); //Exit
    } 
    else
        printf("Sever accepted client\n"); 

    //Start the chat functions to communicate with the connected client
    func(connfd); 
    //Close sever socket
    close(sockfd); 
} 
