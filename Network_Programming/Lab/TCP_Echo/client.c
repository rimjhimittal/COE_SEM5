#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#define PORT 1234 
int main()
{
    int sockfd;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    
    bzero(sendline,100);
    bzero(recvline,100);
    bzero(&servaddr,sizeof(servaddr));
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    //sendline is scanf
    fgets(sendline,100,stdin);
    send(sockfd,sendline,strlen(sendline),0);
    recv(sockfd,recvline,100,0);
    
    printf("%s",recvline);
}
