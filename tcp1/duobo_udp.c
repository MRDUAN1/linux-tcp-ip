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
#define MAXBUFFER 1024
int main(int argc, char *argv[]) 
{
int myfd;
struct sockaddr_in mcastaddr;
int addrlen = sizeof(mcastaddr);
char buffer[MAXBUFFER];
bzero(&mcastaddr);
bzero(buf, sizeof(buf));
if((myfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
printf("sock() wrong :%d, %s\n", errno, strerror(errno));
exit(0);
}
mcastaddr.sin_family = AF_INET;
if(argc > 1){
int res;
res = inet_pton(AF_INET, argv[1], &mcastaddr.sin_addr);
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
if(argc == 3)
{
mcastaddr.sin_port = htons(atoi(argv[2]));
}else{
mcastaddr.sin_port = htons(PORT);
}



















