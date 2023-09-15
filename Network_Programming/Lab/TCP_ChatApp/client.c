#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>

int main(){
	int client_fd;
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	char sendline[100];
	char recvline[100];
	bzero(sendline, 100);
	bzero(recvline, 100);
	
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(1234);
	
	// Connect to the server
	connect(client_fd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
	
	// Send and receive messages
	while(1){
		// Get message from user
		fgets(sendline, 100, stdin);
		
		// Send message to server
		send(client_fd, sendline, sizeof(sendline), 0);
		
		// Receive message from server
		recv(client_fd, recvline, 100, 0);
		
		// Print the received message
		printf("Received Data: %s\n", recvline);
	}
}

abcd