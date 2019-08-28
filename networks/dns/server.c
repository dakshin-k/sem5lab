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

char table[10][25][25];
int nt=1;
void fill()
{
	strcpy(table[0][0],"google.com");
	strcpy(table[0][1],"8.8.8.8");
}
void disp()
{
	printf("%15s   %15s\n", "Domain name","IP Address");
	for (int i = 0; i < nt; ++i)
	{
		printf("%15s   %15s\n",table[i][0],table[i][1]);
	}
}
void modify()
{
	char d[20],ip[20];
	printf("Domain name: ");
	scanf(" %s",d);
	printf("IP address: ");
	scanf(" %s",ip);
}
// Driver code 
int main() { 
	fill();
	printf("Contents of table:\n");
	disp();
	printf("Modify table? y/n: ");
	char c;
	scanf(" %c",&c);
	if(c=='y')
		modify();

	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
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
	printf("Client : %s\n", buffer); 
	sendto(sockfd, (const char *)hello, strlen(hello), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	printf("Hello message sent.\n"); 
	
	return 0; 
} 
