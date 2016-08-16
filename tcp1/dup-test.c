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
#include <assert.h>
int main()
{
int fd, save_fd;
char msg[] = "this is a test of dup()\n";
int test;
fd = open("somefile", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
assert(fd >= 0);
save_fd = dup(0);
printf("save_fd = %d\n", save_fd);
test = dup2(fd, 0);
printf("dup2_1 = %d\n", test);
write(0, msg, strlen(msg));
test = dup2(save_fd, 0);
printf("dup2_2 = %d\n", test);
write(0, msg, strlen(msg));
close(save_fd);
return 0;
}


