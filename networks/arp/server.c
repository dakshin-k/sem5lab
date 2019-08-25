// Client side implementation of UDP client-server model 
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

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char dip[25],sip[25],smac[25],data[25];
	printf("Enter destination IP: ");
	scanf(" %s",dip);
	printf("Enter source IP: ");
	scanf(" %s",sip);
	printf("Enter source MAC: ");
	scanf(" %s",smac);
	printf("Enter 16 bit data: ");
	scanf(" %s",data);
	char hello[150];
	sprintf(hello,"%s|%s|%s",dip,sip,smac);
	// char ans[100];
	// char broadcast='1';
	// int s=sizeof(broadcast);
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	// if(setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&broadcast,&s))
 //    {
 //    	perror("Error setting sock opt\n");
 //    }
	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr("10.6.255.255"); 
	
	int n, len; 
	
	sendto(sockfd, (const char *)hello, strlen(hello), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	printf("ARP request packet:\n%s\n",hello); 
	printf("Waiting for reply...\n");	
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	// printf("n=%d\n", n);
	buffer[n] = '\0'; 
	printf("ARP Reply received: %s\n", buffer); 
	printf("Sending the packet to %s\n", strrchr(buffer,'|')+1);
	sprintf(buffer,"%s|%s",buffer,data);
	printf("Packet: %s\n", buffer);

	close(sockfd); 
	return 0; 
} 
