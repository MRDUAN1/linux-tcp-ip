#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
int main()
{
struct epoll_event ev, events[20];
int fd = epoll_create(10);
epoll_ctl(fd, EPOLL_CTL_ADD, 0, &ev);
if(epoll_wait(fd, events, 20, -1))
{
printf("hello world");
}
close(fd);
} 

