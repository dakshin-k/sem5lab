// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
int main() { 
	int sockfd; 
	char buff[1000]; 
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr; 
	
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
	
	int len, n; 
	if(fork()==0)
	{
		while(1)
		{
			int n, len; 
			n = recvfrom(sockfd, (char *)buff, sizeof(buff), MSG_DONTWAIT, (struct sockaddr *) &cliaddr, &len); 
			if(n==-1)
				continue;
			buff[n] = '\0'; 
			printf("Received %s\n", buff); 
		}
	}
	else
	{
		while(1)
		{		
			scanf(" %s",buff);
			sendto(sockfd, buff, strlen(buff), 
				MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
				sizeof(cliaddr)); 
		}
	}
	
	return 0; 
} 

