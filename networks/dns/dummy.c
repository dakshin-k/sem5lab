#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include<netdb.h>
int main(){
  struct hostent* host=gethostbyname("yahoo.com");
  char ip[30];
  struct sockaddr_in sock_addr;
    sock_addr.sin_addr = *((struct in_addr*) host->h_addr);
    inet_ntop(AF_INET, &sock_addr.sin_addr, ip, sizeof(ip));
    printf("%s\n", ip);
 
  return 0;
}