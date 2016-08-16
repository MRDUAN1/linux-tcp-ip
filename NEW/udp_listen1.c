#include "head"
int tcp_listen(const char *host, const char *serv, sockaddr **saptr, socklen_t *lenp)
{
int sockfdfd, n;
const int on = 1;
struct addrinfo hints, *res, *ressave;
bzero(&hints, sizeof(struct addrinfo));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_DGRAM;
if((n = getaddrinfo(host, serv, &hints, &res)) != 0)
printf("something wrong in %s, %s", host, serv);
ressave = res;
do{
sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
if(sockfd >= 0) break;
}while((res = res->ai_next) != NULL);
if(res == NULL)
printf("something wrong in %s, %s", host, serv);
*saptr = (struct sockaddr*)malloc(res->ai_addrlen);
memcpy(*saptr, res->ai_addr, res->ai_addrlen);
*lenp = res->ai_addrlen;
freeaddrinfo(ressave);
return(sockfd);
}

