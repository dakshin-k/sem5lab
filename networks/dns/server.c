// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include<netdb.h>
extern int h_errno;
#define PORT	 8080 
#define MAXLINE 1024 

char table[10][25][25];
char* find(char *host);
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
	char d[20],ip[20],t[20];
	printf("Domain name: ");
	scanf(" %s",d);
	
	for(;;) // repeat until input ip is valid and unique
	{
		printf("Enter valid IP address: ");
		scanf(" %s",ip);	
		int flag=0;

		//check for valid ip address -> all of the 4 numbers must be <= 255
		strcpy(t,ip); 
		char *tok=strtok(t,".");
		while(tok!=NULL)
		{
			if(atoi(tok)>255)
				flag=1;
			tok=strtok(NULL,".");
		}
		if(flag)
		{
			printf("Invalid IP address!\n");
			continue;
		}

		//now check if ip is already in the table
		for (int i = 0; i < nt; ++i)
		{
			if(!strcmp(ip,table[i][1]))
				flag=1;
		}
		if(flag)
		{
			printf("IP address already exists\n");
			continue;
		}
		strcpy(table[nt][0],d);
		strcpy(table[nt++][1],ip);
		break;
	}
	printf("Updated table is \n");
	disp();
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
	// char *hello = "Hello from server"; 
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
	for(;;){
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
					MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
					&len); 
		buffer[n] = '\0'; 
		char *ans=find(buffer);
		sendto(sockfd, (const char *)ans, strlen(ans), 
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
				len); 
	}
	
	return 0; 
} 


char *find(char host[]){
	//linear search thru table
	int i;
	for (i = 0; i < nt; ++i)
	{
		if(!strcmp(host,table[i][0]))
			break;
	}
	if(i==nt)
	{
		//gethostbyname
		struct hostent *h=gethostbyname(host);
		if(h==NULL)
			return "(Not found)";
		char ip[30];
	    struct sockaddr_in address;
	    address.sin_addr = *((struct in_addr*) h->h_addr);
	    inet_ntop(AF_INET, &address.sin_addr, ip, sizeof(ip));
	    
	    //add this entry to our table
	    strcpy(table[nt][0],host);
	    strcpy(table[nt++][1],ip);

	    //display the new table
	    printf("Contents of table: \n");
	    disp();
	    return table[nt-1][1];
	}
	return table[i][1];

}