#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void interrupt(int signaltype)
{
puts("hello world");
sleep(3);
}

int main(int argc, char *argv[])
{
struct sigaction handler;
handler.sa_handler = interrupt;
if(sigfillset(&handler.sa_mask) < 0)
return;
handler.sa_flags = 0;
sigaction(SIGINT, &handler, 0);
while(1)
pause();
exit(0);
}
