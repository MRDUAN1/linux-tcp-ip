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
int main(){
char *server = argv[1];
char *echostring = argv[2];
char *servport = (argc == 4) ? argv[3] : "echo";
struct addrinfo addrif;
bzero(&addrif, sizeof(addrinfo));
addrif.ai_family = AF_UNSPEC;
addrif.ai_socktype = SOCK_DGRAM;
addrif.ai_protocol = IPPROTO_UDP;
struct addrinfo *serveraddr;
int rtnval = getaddrinfo(server, servport, &addrif, &serveraddr);
if(rtnval != 0){printf("something wrong in getaddrinfo\n"); exit(0);}
int sock = socket(serveraddr->ai_family, serveraddr->ai_socktype, serveraddr->ai_protocol);
int num = sendto(sock, echostring, echostringlen, 0, serveraddr->ai_addr, serveraddr->ai_addrlen);
if(num < 0){printf("wrong in sendo"); exit(0);}
struct sockaddr_storage fromaddr;
socklen_t fromaddrlen = sizeof(fromaddr);
char buffer[1024];
num = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&fromaddr, &fromaddrlen);
freeaddrinfo(servaddr);
buffer[echostringlen] = '\0';
printf("received : %s\n", buffer);
close(sock);
exit(0);
}

