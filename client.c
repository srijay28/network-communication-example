#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int clientSocket;
    char buffer1[1024];
char buffer2[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    int n;

    // Create the socket
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
        perror("Connection failed");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Continuous communication with the server
    while (1) {
        // Clear the buffer
        memset(buffer1, 0, sizeof(buffer1));
	memset(buffer2,0,sizeof(buffer2));

        // Get user input
        printf("Enter message: ");
        fgets(buffer1, sizeof(buffer1), stdin);

        // Send the message to the server
        send(clientSocket, buffer1, strlen(buffer1), 0);

        // Receive the server's response
        n = recv(clientSocket, buffer2, sizeof(buffer2) - 1, 0);
        if (n <= 0) {
            // Connection closed or error occurred
            printf("Connection closed\n");
            close(clientSocket);
            break;
        }

        // Print the server's response
        printf("Server: %s\n", buffer2);
    }

    return 0;
}