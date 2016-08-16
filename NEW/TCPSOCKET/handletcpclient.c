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
#define BUFFSIZE 1024
void handletcpclient(int clnsock)
{
char buffer[BUFFSIZE];
ssize_t numberbyterec = recv(clnsock, buffer, BUFFSIZE, 0);
if(numberbyterec < 0)
fputs("failed rec", stdout);
while(numberbyterec > 0)
{
ssize_t numberbytesent = send(clnsock, buffer, numberbyterec, 0);
if(numberbytesent != numberbyterec)
fputs("failed sent", stdout);
numberbyterec = recv(clnsock, buffer, BUFFSIZE, 0);
if(numberbyterec < 0)
fputs("failed rec", stdout);
}
close(clnsock);
}



