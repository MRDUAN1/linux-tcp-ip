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
#define PRINT(x) printf("wrong in %", x);
int main(int argc, char *argv){
if(argc < 3)PRINT("param");
fd_set sockset;
long timeout = atol(argv[1]);
int portnum = argc - 2;
int serversock[portnum];
int port, maxport;
for(port = 0; port < portnum; port++){
serversock[port] = setupserversock(argv[port + 2]);
if(serversock[port] > maxport)
maxport = serversock[port];}
puts("hit return to showdown");
int running = true;
while(running){
FD_ZERO(&sockset);
FD_SET(0, &sockset);
int port;
for(port = 0; port < portnum; port++)
FD_SET(serversock[port], &sockset);
struct timeval seltimeout;
seltimeout.tv_sec = timeout;
seltimeout.tv_usec = 0;
if(select(maxport + 1, &sockset, NULL, NULL, &seltimeout))
printf("no echo request for %ld secs....server still alive\n", timeout);
else{
if(FD_ISSET(0, &sockset)){
puts("shutting down server");
getchar();
running = false;
}
for(port = 0; port < portnum; port++)
if(FD_ISSET(serversock[port], &sockset)){
printf("request on port %d:", port);
handletcpclient(accepttcpconnection(serversock[port]));
}
}
}
int port;
for(port = 0; port < portnum; port++)
close(serversock[port]);
exit(0);
}

