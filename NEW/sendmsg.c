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
listenfd = tcp_connect(NULL, argv[1]);
fgets(buf,1024,stdin); 
ssize_t size = sendmsg(listenfd, &msg, 0);
close(listenfd);
exit(0);
}


