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
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(1029); 
	servaddr.sin_addr.s_addr = inet_addr("10.6.12.9"); 
	if(fork()==0)
	{
		while(1)
		{
			int n, len; 
			n = recvfrom(sockfd, (char *)buff, sizeof(buff), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
			if(n==-1)
				continue;
			buff[n] = '\0'; 
			printf("%s\n", buff); 
		}
	}
	else
	{
		while(1)
		{		
			scanf(" %s",buff);
			sendto(sockfd, buff, strlen(buff), 
				MSG_DONTWAIT, (const struct sockaddr *) &servaddr, 
					sizeof(servaddr)); 
		}
	}
	close(sockfd); 
	return 0; 
} 

