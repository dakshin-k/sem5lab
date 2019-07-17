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
	servaddr.sin_port = htons(1030); 
	servaddr.sin_addr.s_addr = inet_addr("10.6.12.9"); 
	
	int n, len; 
	printf("Enter message: ");
	scanf(" %s",buff);
	sendto(sockfd, buff, strlen(buff), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	printf("message sent.\n"); 
		
	n = recvfrom(sockfd, (char *)buff, sizeof(buff), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
	buff[n] = '\0'; 
	printf("Received %s\n", buff); 

	close(sockfd); 
	return 0; 
} 

