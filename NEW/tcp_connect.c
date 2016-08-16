#include "head.h"
#include <assert.h>
int tcp_connect(const char *host, const char *serv)
{
int sockfd, n;
struct addrinfo hints, *res, *ressave;
bzero(&hints, sizeof(struct addrinfo));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
assert(getaddrinfo(host, serv, &hints, &res) != 0);
ressave = res;
do{
sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
if(sockfd < 0) continue;
if(connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
break;
close(sockfd);
}while((res = res->ai_next) != NULL);
assert(res != NULL);
freeaddrinfo(ressave);
return (sockfd);
}

