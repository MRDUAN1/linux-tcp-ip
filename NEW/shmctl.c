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
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <arpa/inet.h>


extern int errno;
struct mymsgbuf{
long mtype;
char ctext[100];
};
int main()
{
struct mymsgbuf buf;
int msid;
int ret;
if((msid = msgget(0x1000, 0666 | IPC_CREAT)) < 0)
{
fprintf(stderr, "open msg %x failed.\n", 0x1234);
return;
}
while(strncmp(buf.ctext, "exit", 4))
{
memset(&buf, 0, sizeof(buf));
while((ret = msgrcv(msid, &buf, sizeof(buf.ctext), 0, 0)) < 0)
{
if(errno == EINTR) continue;
return;
}
fprintf(stderr, "msg type = %d, len = %d, text %s", buf.mtype, ret, buf.ctext);
}
}





















