#include "public.h"
int setuptcpclientsocket(const char *host, const char *service)
{
struct addrinfo addr;
memset(&addr, 0, sizeof(addr));
addr.ai_family = AF_UNSPEC;
addr.ai_socktype = SOCK_STREAM;
addr.ai_protocol = IPPROTO_TCP;
struct addrinfo *addrlist;
int renval = getaddrinfo(addstring, portstring, &addr, &addrlist);
struct addrinfo *addrl = addrlist;
int sock = -1;
for(addrlist; addrl != NULL; addrl = addrl->ai_next)
{
sock = socket(addrl->ai_family, addrl->ai_socktype, addrl->ai_protocol);
if(sock < 0)
continue;
if(connect(sock, addrl->ai_addr, addr->ai_addrlen) == 0)
break;
close(sock);
sock = -1;
}
freeaddrinfo(addrlist);
return sock;
}
