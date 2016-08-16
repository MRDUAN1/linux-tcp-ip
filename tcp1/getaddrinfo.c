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
#include <arpa/inet.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
void printsocketaddr(const struct sockaddr *address, FILE *stream);
int main(int argc, char *argv[])
{
//char *addstring = argv[1];
char *portstring = argv[2];
struct addrinfo addr;
memset(&addr, 0, sizeof(addr));
addr.ai_family = AF_UNSPEC;
addr.ai_socktype = SOCK_STREAM;
addr.ai_protocol = IPPROTO_TCP;
struct addrinfo *addrlist;
int renval = getaddrinfo(NULL, portstring, &addr, &addrlist);
struct addrinfo *addrl = addrlist;
for(addrlist; addrl != NULL; addrl = addrl->ai_next)
{
printsocketaddr(addrl->ai_addr, stdout);
fputc('\n', stdout);
}
freeaddrinfo(addrlist);
exit(0);
}




void printsocketaddr(const struct sockaddr *address, FILE *stream)
{if(address == NULL || stream == NULL)
return 0;
void *numadd;
char addbuffer[1000];
in_port_t port;
switch(address->sa_family){
case AF_INET:
numadd = &((struct sockaddr_in *)address)->sin_addr;
port = ntohs(((struct sockaddr_in *)address)->sin_port);
break;
case AF_INET6:
numadd = &((struct sockaddr_in6 *)address)->sin6_addr;
port = ntohs(((struct sockaddr_in6 *)address)->sin6_port);
break;
default:
fputs("unknown type", stream);
return 0;
}
if(inet_ntop(address->sa_family, numadd, addbuffer, sizeof(addbuffer)) == NULL)
fputs("invalid address", stream);
else{
fprintf(stream, "%s", addbuffer);
if(port != 0)
fprintf(stream, "-%u", port);
}
}
