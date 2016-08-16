#include <stdio.h>
#include <unistd.h>
int main(int argc , char *argv[])
{
if (argc != 2)
fputs("failed argc", stdout);
char *service = argv[1]; //local port
int servsock = setupserversock(service);
if(servsock < 0)
fputs("servsock erron", stdout);
for(; ;)
{
int clnsock = accepttcpconnection(servsock);
handletcpclient(clnsock);
close(clnsock);
}
}
