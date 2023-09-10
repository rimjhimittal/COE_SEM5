#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 1234
int main(){
    char str[100];
    int server_fd, client_fd;
    struct sockaddr_in servaddr;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET; // Set the address family to IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on any IP address
    servaddr.sin_port = htons(PORT); 
    bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(server_fd, 5);
    client_fd = accept(server_fd,(struct sockaddr *)NULL, NULL);
    recv(client_fd,str,100,0); //hardcoded 100 because we do not know length of incoming stream
    printf("Received data is %s",str);
    send(client_fd,str,strlen(str),0);
    //0 is flag operation...tells abt successfull and unsuccessfull op
    close(client_fd);
}