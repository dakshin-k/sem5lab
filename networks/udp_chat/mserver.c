// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <pthread.h>
struct sockaddr_in cliaddr;
struct sockaddr_in cl1,cl2;
int f1=0,f2=0; 
int len,sockfd;
char buff[1000]; 

int equals(struct sockaddr_in a,struct sockaddr_in b)
{
	return (a.sin_addr.s_addr==b.sin_addr.s_addr);
}
void* recvthread(void *p)
{
	while(1)
	{
		int n, len; 
		n = recvfrom(sockfd, (char *)buff, sizeof(buff), MSG_WAITALL, (struct sockaddr *) &cliaddr, &len); 
		if(f1==0)
		{
			cl1=cliaddr;
			f1=1;
		}
		if(f2==0)
		{
			cl2=cliaddr;
			f2=1;
		}
		if(n==-1)
			continue;
		buff[n] = '\0'; 
		printf("Client%d: %s\n", equals(cliaddr,cl1)? 1:2,buff); 
	}
	pthread_exit(0);
}
int main() { 
	
	struct sockaddr_in servaddr;
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(1029); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	pthread_t pid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&pid,&attr,recvthread,NULL);
	{
		while(1)
		{		
			scanf(" %s",buff);
			sendto(sockfd, buff, strlen(buff), 
				MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
				sizeof(cliaddr)); 
		}
	}
	pthread_join(pid,NULL);
	return 0; 
} 

