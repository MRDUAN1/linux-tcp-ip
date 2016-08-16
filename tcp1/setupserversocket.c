#define MAXPENDING 5
#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <assert.h>
int setupserversocket(const char *service)
{
struct addrinfo addrcriteria;
addrcriteria.ai_family = AF_UNSPEC;
addrcriteria.ai_flags = AI_PASSIVE;
addrcriteria.ai_socktype = SOCK_STREAM;
addrcriteria.ai_protocol = IPPROTO_TCP;
struct addrinfo *servaddr;
int rtnval = getaddrinfo(NULL, service, &addrcriteria, &servaddr);
if(rtnval != 0){printf("something wrong \n"); exit(0);}
int servsock = -1;
struct addrinfo *addr = servaddr;
for(servaddr ;addr != NULL; addr = addr->ai_next){
servsock = socket(servaddr->ai_family, servaddr->ai_socktype, servaddr->ai_protocol);
if(servsock < 0)
continue;
if((bind(servsock, servaddr->ai_addr, servaddr->ai_addrlen) == 0) && (listen(servsock, MAXPENDING) == 0)){
struct sockaddr_storage localaddr;
socklen_t addrsize = sizeof(localaddr);
if(getsockname(servsock, (struct sockaddr *)&localaddr, &addrsize) < 0)
printf("getsockname() failed");
fputs("binding to ", stdout);
break;
}
close(servsock);
servsock = -1;}

freeaddrinfo(servaddr);
return servsock;
}



