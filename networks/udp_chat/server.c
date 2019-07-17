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
#include<errno.h>

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
    	n=recvfrom(sockfd,buff,sizeof(buff),MSG_WAITALL,NULL,NULL);
    	buff[n]='\0';
    	printf("Recieved %s\n", buff);
    	printf("Enter message: ");// github.com/dakshin-k/sem5lab.git
    	scanf(" %s",buff);
        n=sendto(sockfd, (const char *)buff, strlen(buff),  
        MSG_WAITALL, (const struct sockaddr *) &cliaddr, 
            len); 
         
    	if(n==-1)
    	   printf("errno = %d\n",errno);
        close(sockfd);
        return 0;
}
