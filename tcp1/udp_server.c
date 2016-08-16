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
char *service = argv[1];
struct addrinfo *addrif;
addrif.ai_family = AF_UNSPEC;
addrif.ai_flags = AF_PASSIVE;
addrif.ai_socktype = SOCK_DGRAM;
addrif.ai_protocol = IPPROTO_UDP;
struct addrif *serveraddr;
int rtnval = getaddrinfo(NULL, service, &addrif, &serveraddr);
int sock = socket(servaddr->ai_family, servaddr->ai_socktype, servaddr->protocol);
if(bind(sock, serveraddr->ai_addr, serveraddr->ad_addrlen) < 0)
printf("wrong in bind\n");
freeaddrinfo(serveraddr);
while(1){
struct sockaddr_strorage clnaddr;
socklen_t clnaddrlen = sizeof(clnaddr);
char buffer[1024];
int num = recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&clnaddr, &clnaddrlen);
fputs("handle client", stdout);












