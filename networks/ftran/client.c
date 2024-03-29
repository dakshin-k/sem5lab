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

if(argc<5)
{
   printf("Usage: Source IP; port no; source file name; dest file name\n");
   return 0;
}
int len;
int sockfd,n;
int r;
struct sockaddr_in servaddr,cliaddr;
char buff[1024];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
perror("cannot create socket");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
servaddr.sin_port=htons(atoi(argv[2]));
r=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(r==-1)
{
   printf("Connect returned %d\n",r);
   printf("Errorno = %d\n",errno);
   return 0;
}
//send the file name
write(sockfd,argv[3],strlen(argv[3]));

//get response -> either 404 or first line of file
n=read(sockfd,buff,sizeof(buff));

if(!strcmp(buff,"404"))
{
   printf("File not found\n");
   close(sockfd);
   return 0;
}
write(sockfd,buff,1);
buff[n]='\0';
int file=open(argv[4],O_CREAT|O_WRONLY|O_TRUNC);
if(file==-1)
{
   printf("error creating file\n");
   close(sockfd);
   return 0;
}
write(file,buff,strlen(buff));
while(1)
{
   //read from socket & write to file -- unless string is "\0"
   n=read(sockfd,buff,sizeof(buff));
   buff[n]='\0';
   write(sockfd,buff,1);
   if(!strcmp(buff,"\0"))
      break;
   
   write(file,buff,strlen(buff));
}
close(file);
close(sockfd);
printf("File successfully copied.\n");
return 0;
}
