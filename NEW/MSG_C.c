#include "head.h"
static int connfd;
int main(int argc, char **argv)
{
char buffer[1024];
void sig_usr(int arg);
int listenfd, i;
socklen_t addrlen;
listenfd = tcp_listen(NULL, argv[1], NULL);
struct sigaction handler;
handler.sa_handler = sig_usr;
sigfillset(&handler.sa_mask);
sigaction(SIGURG, &sig_usr, 0);
struct sockaddr_in connfd_c;
while(1){
int sin_size = sizeof(connfd_c);
connfd = accept(listenfd, (struct sockaddr*)&connfd_c, &sin_size);
fcntl(connfd, F_SETOWN, getpid());
while(1){
int ret = recv(connfd, buffer, 1023, 0);
printf("%s\n", buffer);
}
close(connfd);
}
}

void sig_usr(int arg)
{
int save_errno = errno;
char buffer[20];
bzero(buffer, sizeof(buffer));
int ret = recv(connfd, buffer, 1023, MSG_OOB);
printf("got the oob data %s\n", buffer);
errno = save_errno;
}


