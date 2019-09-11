// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 1029 
#define MAXLINE 1024 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char cip[20];
	char cmac[20];
	char smac[20];
	printf("Enter the IP address: ");
	scanf(" %s",cip);
	printf("Enter the MAC address: ");
	scanf(" %s",cmac);

	char ans[100];

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
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n; 
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("ARP request receieved: %s\n", buffer); 
	char c[100];
	strcpy(c,buffer);
	char *tok=strtok(c,"|");
	// printf("%s\n", buffer);
	if(!strcmp(tok,cip))
	{
		//arp request was meant for you
		printf("IP address matches\n");

		sprintf(buffer,"%s|%s",buffer,cmac);
		//send this value out
		strcpy(ans,buffer);
		//printf("\n%s: len=%d\n", ans,strlen(ans));		
		n=sendto(sockfd, (const char *)ans, strlen(ans), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
		if (n==-1)
			perror("sendto failed"); 
		printf("ARP reply sent: %s\n",ans); 
	}
	else
		printf("IP address does not match.\n");
	
	//start of RARP
	printf("Enter the server MAC address: ");
	scanf(" %s",smac);
	sprintf(buffer,"RARP|%s|%s",smac,cmac);
	n=sendto(sockfd, (const char *)buffer, strlen(buffer), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			sizeof(cliaddr)); 
		if (n==-1)
			perror("sendto failed"); 
	printf("RARP request sent\n");
	printf("Waiting for reply...\n");
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("RARP reply received: %s\n", buffer);
	return 0; 
} 
