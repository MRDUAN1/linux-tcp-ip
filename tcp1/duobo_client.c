#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#define MAXBUFFER 1024
int main(int argc, char *argv[]) 
{
int myfd, clientfd;
struct sockaddr_in myaddr, clientaddr;
struct ip_mreq mreq;
int addrlen = sizeof(clientaddr);
char buffer[MAXBUFFER];
char addrtemp[INET_ADDRSTRLEN];
bzero(&myaddr, sizeof(myaddr));
bzero(&clientaddr, sizeof(clientaddr));
myfd = socket(AF_INET, SOCK_DGRAM, 0);
assert(myfd != -1);
if(argc == 3)
{
myaddr.sin_port = htons(atoi(argv[2]));
}else{
myaddr,sinport = htons(PORT);
}
int temp = bind(myfd, (struct sockaddr *)&myaddr, sizeof(myaddr);
assert(!temp);
u_char loop = 1;
temp = setsockopt(myfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
assert(!temp);
u_char ttl = 1;
temp = setsockopt(myfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
assert(!temp);
if(argc > 1){
int res;
res = inet_pton(AF_INET, argv[1]; &mreq.imr_multiaddr);
assert(res != -1);
if(res == 0){
printf("ip invaild\n");
printf("please input another\n");
exit(0);
}
}
else{
printf("usage %s duobo ip addr\n", argv[0]);
return 0;
}
mreq.imr_interface.s_addr = INADDR_ANY;
temp = setsockopt(myfd, IPPROTO_IP, IP_ADD_MEMEERSHIP, &mreq, sizeof(mreq));
assert( temp != 0);
printf("client start\n");
while(1){
bzero















