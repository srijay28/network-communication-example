#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    int welcomeSocket, newSocket;
    char buffer1[1024];
char buffer2[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    int n;

    // Create the socket
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (welcomeSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    // Bind the address struct to the socket
    if (bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(welcomeSocket);
        exit(EXIT_FAILURE);
    }

    // Listen on the socket, with 5 max connection requests queued
    if (listen(welcomeSocket, 5) == 0)
        printf("Listening! Type end to end connection\n");
    else {
        perror("Listen failed");
        close(welcomeSocket);
        exit(EXIT_FAILURE);
    }

    // Accept call creates a new socket for the incoming connection
    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    if (newSocket < 0) {
        perror("Accept failed");
        close(welcomeSocket);
        exit(EXIT_FAILURE);
    }

    // Continuous communication with the client
    while (1) {
        // Clear the buffer
        memset(buffer1, 0, sizeof(buffer1));
memset(buffer2,0,sizeof(buffer2));

        // Receive message from the client
        n = recv(newSocket, buffer1, sizeof(buffer1) - 1, 0);
        if (n <= 0) {
            // Connection closed or error occurred
            printf("Connection closed\n");
            close(newSocket);
            break;
        }

        // Print the received message
        printf("Received: %s\n", buffer1);

        printf("Send Message: ");
fgets(buffer2,sizeof(buffer2),stdin);
	if (strcmp(buffer2,"end")== 0){
	close(welcomeSocket);
	}
        send(newSocket, buffer2, strlen(buffer2), 0);
    }

    // Close the welcome socket
    close(welcomeSocket);

    return 0;
}
