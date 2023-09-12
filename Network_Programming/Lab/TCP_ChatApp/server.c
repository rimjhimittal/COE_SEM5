#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
	int server_fd, client_fd;	
	struct sockaddr_in servaddr, cliaddr;	
	char str[100];	
	char sendline[100];
	
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
	client_fd = accept(server_fd, (struct sockaddr *) NULL, NULL);
	
	// Receive and send messages
	while(1){
		// Receive message from client
		recv(client_fd, str, 100, 0);
		
		// Print the received message
		printf("Received Data is %s\n", str);
		
		// Get message from user
		fgets(sendline, 100, stdin);
		
		// Send message to client
		send(client_fd, sendline, strlen(sendline), 0);
	}
	
	// Close the socket
	close(client_fd);
}

