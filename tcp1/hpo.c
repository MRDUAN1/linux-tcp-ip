#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
int main(int argc, char *argv[])
{
char *addrstring = argv[1];
char *portstring = argv[2];
struct addrinfo addrcriteria;
addrcriteria.ai_family = AF_UNSPEC;
addrcriteria.ai_flags = AI_PASSIVE;
addrcriteria.ai_socktype = SOCK_STREAM;
addrcriteria.ai_protocol = IPPROTO_TCP;
struct addrinfo *servaddr;
int rtnval = getaddrinfo(addstring, portstring, &addrcriteria, &servaddr);
for(struct addrinfo *addr = servaddr; addr != NULL; addr = addr->ai_next){
printsocketaddress(addr->ai_addr, stdout);
fputc('\n', stdout);
}
freeaddrinfo(servaddr);
exit(0);
}

