#include "head.h"
int fd;
void hello(int signum)
{
unsigned char key_val;
read(fd, &key_val, 1);
printf("key_val:0x%x\n", key_val);
}
int main()
{
int oflags;
struct sigaction handler;
handler.sa_handler = hello;
handler.sa_flags = 0;
sigaction(SIGIO, &hello, 0);
fd = open("/dev/buttons", O_RDWR | O_NONBLOCK);
if(fd < 0){
printf("cantt open");
exit(0);
}
fcntl(fd, F_SETOWN, getpid());
oflags = fcntl(fd, F_GETFL);
fcntl(fd, F_SETFL, oflags | FASYNC);
while(1)
sleep(1000);
return 0;
}
