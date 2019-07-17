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
	struct sockaddr_in servaddr, cliaddr; 
	
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
	servaddr.sin_port = htons(6666); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n; 
	n = recvfrom(sockfd, buff, sizeof(buff), 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buff[n] = '\0'; 
	printf("Received %s\n", buff); 
	strcpy(buff,"reply");
	sendto(sockfd, buff, strlen(buff), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	printf("message sent.\n"); 
	
	return 0; 
} 

