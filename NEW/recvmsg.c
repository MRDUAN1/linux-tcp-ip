#include "head.h"
int main(int argc, char **argv){
int listenfd, i;
char buf[1024];
struct sockaddr *clientaddr;
socklen_t addrlen;
struct msghdr msg;
msg.msg_name = NULL;
struct iovec io;
io.iov_base = buf;
io.iov_len = 1024;
msg.msg_iov = &io;
msg.msg_iovlen = 1;
listenfd = tcp_listen(NULL, argv[1], &addrlen);
while(1){
int sin_size = sizeof(clientaddr);
int connfd = accept(listenfd, clientaddr, &sin_size);
ssize_t recv_size = recvmsg(connfd, &msg, 0);
char *temp = msg.msg_iov[0].iov_base;
temp[recv_size] = '\0';
printf("get message : %s", temp);
}
}


