#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in servaddr, cliaddr;
    char str[100];
    char sendline[100];
    int year;

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind the socket to a port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(1234);
    bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Listen for connections
    listen(server_fd, 5);

    // Accept a connection
    client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL);

    // Receive year from client
    recv(client_fd, str, 100, 0);
    str[strlen(str)] = '\0'; // Add null terminator

    int i, j;

    // Check if the string is a palindrome
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        if (str[i] != str[j]) {
            send(client_fd, "Not Palindrome", strlen("Not Palindrome") + 1, 0);
            break;
        }
    }
        send(client_fd, "Palindrome", strlen("Palindrome") + 1, 0);
    

    // Close the socket
    close(client_fd);
}
