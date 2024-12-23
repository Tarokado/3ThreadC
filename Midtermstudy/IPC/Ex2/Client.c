#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    float a, b, c;

    printf("Enter coefficients a, b, and c: ");
    scanf("%f %f %f", &a, &b, &c);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    send(sock, &a, sizeof(float), 0);
    send(sock, &b, sizeof(float), 0);
    send(sock, &c, sizeof(float), 0);

    int num_roots;
    float root1, root2;
    read(sock, &num_roots, sizeof(int));
    read(sock, &root1, sizeof(float));

    if (num_roots == 2) {
        read(sock, &root2, sizeof(float));
        printf("Roots are: %.2f and %.2f\n", root1, root2);
    } else if (num_roots == 1) {
        printf("Root is: %.2f\n", root1);
    } else {
        printf("No real roots.\n");
    }

    close(sock);
    return 0;
}
