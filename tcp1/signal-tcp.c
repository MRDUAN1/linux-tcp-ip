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
#include <signal.h>
int sock;
#define PRINT(x) printf("wrong in %s", x);
int main(int argc, char *argv){
char *service = argv[1];
struct addrinfo addrif;
bzero(&addrif, sizeof(addrinfo));
addrif.ai_family = AF_UNSPEC;
addrif.ai_socktype = SOCK_DGRAM;
addrif.ai_protocol = IPPROTO_UDP;
struct addrinfo *serveraddr;
int rtnval = getaddrinfo(server, servport, &addrif, &serveraddr);
if(rtnval != 0){PRINT(getaddrinfo); exit(0);}
sock = socket(serveraddr->ai_family, serveraddr->ai_socktype, serveraddr->ai_protocol);
if(bind(sock, serveraddr->ai_addr, serveraddr->ad_addrlen) < 0)
PRINT("bind");
freeaddrinfo(serveraddr);
struct sigaction handler;
handler.sa_handler = signohandler;
if(sigfillset(&handler.sa_mask) < 0)PRINT(sigfillset);
handler.sa_flags = 0;
if(sigaction(SIGIO, &handler, 0) < 0)
PRINT(sigaction);
if(fcntl(sock, F_SETOWN, getpid()) < 0)
PRINT("fcntl own");
if(fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
PRINT("fcntl");
while(1)useidtime();
}

void useidtime(){
puts(".");
sleep(3);
}

void signohandler(int signaltype){
int num;
do{
struct sockadddr_storage clnaddr;
int clntlen = sizeof(clnaddr);
char buffer[1024];
num = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&clnaddr, &clntlen);
if(num < 0)PRINT("recvfrom");
fputs(buffer, stdout);
fputs('\n', stdout);
int send_num = sendto(sock, buffer, 1024, 0, (struct sockaddr *)&clnaddr, sizeof(clnaddr));
}
while(num >= 0)
}

