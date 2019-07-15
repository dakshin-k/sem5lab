#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char **argv)
{

int len,r;
int sockfd,n;
struct sockaddr_in servaddr,cliaddr;
char buff[1024];
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)
perror("cannot create socket");
memset(&servaddr, 0, sizeof(servaddr)); 
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(6666);
r=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(r==-1)
{
   printf("Connect returned %d\n",r);
   printf("Errorno = %d\n",errno);
   return 0;
}
//send the file name
write(sockfd,"bitch",5);

close(sockfd);
return 0;

}
