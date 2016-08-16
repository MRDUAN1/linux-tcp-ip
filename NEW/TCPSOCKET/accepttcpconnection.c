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
int accepttcpconnection(int servsock)
{
struct sockaddr_storage clnaddr;
int clnaddrlen = sizeof(clnaddr);
int clnsock = accept(servsock, (struct sockaddr *)&clnaddr, &clnaddrlen);
if(clnsock < 0)
printf("accept() failed");
fputs("handling client", stdout);
printsocketaddr((struct sockaddr *)&clnaddr, stdout);
fputc('\n', stdout);
return clnsock;
}
