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

char table[5][20][20];
void fill()
{
	strcpy(table[0][0],"192.168.0.1");
	strcpy(table[0][1],"aa-bb-cc-dd-ee");
	strcpy(table[1][0],"192.168.0.2");
	strcpy(table[1][1],"ff-ff-ff-ff-ff");
}
char* rarp(char mac[])
{
	for (int i = 0; i < 2; ++i)
	{
		if(!strcmp(table[i][1],mac))
			return table[i][0];
	}
	return "NOT FOUND";
}
// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	fill();
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

	int bcast_sock = socket(AF_INET, SOCK_DGRAM, 0);
	int broadcastEnable=1;
	int ret=setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, 
	   &broadcastEnable, sizeof(broadcastEnable));	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST); //inet_addr("10.6.255.255"); 
	
	int n, len; 
	
	sendto(bcast_sock, (const char *)hello, strlen(hello), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	printf("ARP request packet:\n%s\n",hello); 
	printf("Waiting for reply...\n");	
	n = recvfrom(bcast_sock, (char *)buffer, MAXLINE, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	// printf("n=%d\n", n);
	buffer[n] = '\0'; 
	printf("ARP Reply received: %s\n", buffer); 
	printf("Sending the packet to %s\n", strrchr(buffer,'|')+1);
	sprintf(buffer,"%s|%s",buffer,data);
	printf("Packet: %s\n", buffer);

	//receive RARP request
	n = recvfrom(bcast_sock, (char *)buffer, MAXLINE, 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	// printf("n=%d\n", n);
	buffer[n] = '\0';
	printf("RARP Request: %s\n", buffer);
	strcpy(hello,buffer);
	//retrieve cmac from buffer
	char *tok=strtok(hello,"|");
	tok=strtok(NULL,"|");
	tok=strtok(NULL,"|");
	sprintf(buffer,"%s|%s",buffer,rarp(tok));
	printf("RARP reply: %s\n", buffer);
	n=sendto(bcast_sock, (const char *)buffer, strlen(buffer), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	if(n==-1)
		perror("RARP sendto failed");
	
	close(sockfd); 
	return 0; 
} 
