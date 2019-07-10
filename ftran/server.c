#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char **argv)
{
        int len,n;
        int sockfd,newfd;
        struct sockaddr_in servaddr,cliaddr;
        char buff[10];
        char str[1000];
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(sockfd<0)
        perror("cannot create socket");
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(atoi(argv[1]));
        if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        perror("Bind error");
        listen(sockfd,4);
        for(int i=0;i<4;i++)
        {
                len=sizeof(cliaddr);
                printf("Waiting for connection\n");
                newfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
                printf("Connected\n");
                // get the file name from the client
                n=read(newfd,buff,sizeof(buff));
                printf("Requested: %s\n",buff);
                int filefd=open(buff,O_RDONLY);
                if(filefd==-1)
                {
                       printf("file not found\n");
                       write(newfd,"404",sizeof("404"));
                       close(newfd);
                       continue;
                }
                while(read(filefd,buff,sizeof(buff))!=0)
                {
                    printf("%s",buff);
                    write(newfd,buff,sizeof(buff));
                    read(newfd,buff,1);
                }
                // inform client that file is over
                write(newfd,"\0",sizeof("\0"));
                close(filefd);
                close(newfd);
        }
        close(sockfd);
        return 0;
}
