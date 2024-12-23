#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

#define PORT 8080

void calculate_roots(float a, float b, float c, float *root1, float *root2, int *num_roots) {
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        *num_roots = 2;
        *root1 = (-b + sqrt(discriminant)) / (2 * a);
        *root2 = (-b - sqrt(discriminant)) / (2 * a);
    } else if (discriminant == 0) {
        *num_roots = 1;
        *root1 = *root2 = -b / (2 * a);
    } else {
        *num_roots = 0;
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    float a, b, c;
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for connections...\n");
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    read(new_socket, &a, sizeof(float));
    read(new_socket, &b, sizeof(float));
    read(new_socket, &c, sizeof(float));
    
    float root1, root2;
    int num_roots;
    calculate_roots(a, b, c, &root1, &root2, &num_roots);

    send(new_socket, &num_roots, sizeof(int), 0);
    send(new_socket, &root1, sizeof(float), 0);
    if (num_roots == 2) {
        send(new_socket, &root2, sizeof(float), 0);
    }

    printf("Roots calculated and sent to the client.\n");
    close(new_socket);
    close(server_fd);
    return 0;
}
