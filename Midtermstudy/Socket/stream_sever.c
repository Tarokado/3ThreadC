#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define LISTEN_BACKLOG 50
#define BUFF_SIZE 256
#define handle_error(msg)\ 
    do{perror(msg); exit(EXIT_FAILURE); } while(0)


//Chuc nang chat 
void chat_func(int new_socket_fd){
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    while(1){
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        //Doc du lieu tu socket
        //Ham read se duoc block cho den khi doc duoc du lieu
        numb_read = read(new_socket_fd,recvbuff,BUFF_SIZE);
        if(numb_read == 1){
            handle_error("read");
        }
    }
}