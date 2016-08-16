#include "head.h"
int main(int argc, char **argv)
{
int n, nready, maxi;
int listenfd, maxfd, connfd;
struct sockaddr_in cliaddr, servaddr;
fd_set readset, allset;
int client[1024];
for(n = 0; n < 1024; n++)
client[n] = -1;
listenfd = tcp_listen(NULL, argv[1], NULL);
maxfd = listenfd;
FD_ZERO(&allset);
FD_SET(listenfd, &allset);
while(1){
readset = allset;
nready = select(maxfd + 1, &readset, NULL, NULL, NULL);
if(FD_ISSET(listenfd, &readset)){
int clilen = sizeof(cliaddr);
int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
int i;
for(i = 0; i < 1024; i++)
if(client[i] < 0){
client[i] = connfd; break;
if(i == 1024){printf("too much\n"); break;}
FD_SET(connfd, &allset);
if(connfd > maxfd) maxfd = connfd;
if(i > maxfd) maxi = i;
if(--nready <= 0) continue;
}
for(i = 0; i <= maxi; i++){
if((sockfd = client[i]) < 0) continue;
if(FD_ISSET(sockfd, &readset)){
if((n = read(sockfd, buf, 1024)) == 0){
close(sockfd);
FD_CLR(sockfd, &allset);
client[i] = -1;
}else{
puts("make in input\n");
scanf("%s", buf);
write(sockfd, buf, n);
bzero(buf, sizeof(buf));
}
if(--nready <= 0) break;
}
}
}

















