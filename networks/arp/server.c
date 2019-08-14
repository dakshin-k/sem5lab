// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr;
	char table[50][50][50];

	//todo: get input for table from user later
	strcpy(table[0][0],"10.6.12.9");
	strcpy(table[0][1],"10:78:D2:83:1A:0F");
	strcpy(table[1][0],"10.6.12.10");
	strcpy(table[1][1],"10:78:d2:da:45:d3");
 
	
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
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n,i; 
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Client : %s\n", buffer); 
	for (int i = 0; i < 2; ++i)
	{
		if(!strcmp(table[i][0],buffer))
			break;
	}
	printf("i=%d\n", i);
		sendto(sockfd, "meow :)", strlen("meow :)"), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len);
	printf("Hello message sent.\n"); 
	
	return 0; 
} 
// 