#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char **argv)
{
        int len,n;
        int sockfd,newfd;
        struct sockaddr_in servaddr,cliaddr;
        char buff[100];
        sockfd=socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd<0)
        perror("cannot create socket");
        bzero(&servaddr,sizeof(servaddr));
        bzero(&cliaddr,sizeof(cliaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(atoi(argv[1]));
        if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        perror("Bind error");
    	n=recvfrom(sockfd,buff,sizeof(buff),MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
    	buff[n]='\0';
    	printf("Recieved %s from %s\n", buff,(char*)inet_ntoa(cliaddr.sin_addr));
        close(sockfd);
        return 0;
}
