#include "head.h"
int main(int argc, char **argv)
{
int listenfd, connfd;
socklen_t len;
char buff[1024];
time_t ticks;
struct sockaddr_storage cliaddr;
listenfd = tcp_listen(NULL, argv[1], NULL);
while(1){
len = sizeof(cliaddr);
connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
printf("gggg\n");
}}
