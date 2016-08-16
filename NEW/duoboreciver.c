#include "head.h"
int main(int argc, char **argv)
{
char *multicastaddrstring = argv[1];
char *service = argv[2];
struct addrinfo addrcriteria;
bzero(&addrcriteria, sizeof(addrcriteria));
addrcriteria.ai_family = AF_UNSPEC;
addrcriteria.ai_socktype = SOCK_DGRAM;
addrcriteria.ai_protocol = IPPROTO_UDP;
addrcriteria.ai_flags |= AI_NUMERICHOST;
struct addrinfo *multicastaddr;
int rnval = getaddrinfo(multicastipstring, service, &addrcriteria, &multicastaddr);
int sock = socket(multicastaddr->ai_family, multicastaddr->ai_socktype, multicastaddr->ai_protocol);
bind(sock, multicastaddr->ai_addr, multicastaddr->ai_addrlen);
struct ip_mreq joinrequest;
joinrequest.imr_multiaddr = ((struct sockaddr_in *)multicastaddr->ai_addr)->sin_addr;
joinrequest.imr_interface.s_addr = 0;
printf("join the grop\n");
setsockopt(sock, IPPOTO_IP, IP_ADD_MEMBERSHIP, &joinrequest, sizeof(joinrequest));
freeaddrinfo(multicastaddr);
char recvstring[1024];
int recvlen = recvform(sock, recvstring, 1023, 0, NULL, 0);
recvstring[recvlen + 1] = '\0';
printf("recvived %s\n", recvstring);
close(sock);
exit(0);
}
