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
#define port 4444
int main()
{
int processlimit = 10;
int process;
int n, sin_size;
int sock_fir, sock_sec;
pthread_t pid, pid_master;
struct sockaddr_in sockaddr_fir; 
struct sockaddr_in sockaddr_sec;
bzero(&sockaddr_fir, sizeof(struct sockaddr_in));
sockaddr_fir.sin_family = AF_INET;
sockaddr_fir.sin_port = htons(port);
sockaddr_fir.sin_addr.s_addr = htonl(INADDR_ANY);
sock_fir = socket(AF_INET, SOCK_STREAM, 0);
//int flags = fcntl(sock_fir, F_GETFL, 0);
//fcntl(sock_fir, F_SETFL, flags | O_NONBLOCK);
setsockopt(sock_fir,SOL_SOCKET,SO_REUSEADDR,&n,sizeof(int));
if(bind(sock_fir, (struct sockaddr *)&sockaddr_fir, sizeof(struct sockaddr)) == -1)
{
printf("something wrong in bind");
exit(0);
}

if(listen(sock_fir, 5) == -1)
{printf("something wrong in listen");
exit(0);
}
while(1)
{
accept(sock_fir, NULL, NULL);
printf("hello\n");
}
close(sock_fir);
}
