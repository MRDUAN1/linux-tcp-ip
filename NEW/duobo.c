#include "head.h"
int main(int argc, char **argv)
{
char *multicastipstring = argv[1];
char *service = argv[2];
char *sending = argv[3];
size_t sendstringlen = strlen(sending);
int multicastttl = (argc == 5) ? atoi(argv[4]) : 1;
struct addrinfo addrcriteria;
bzero(&addrcriteria, sizeof(addrcriteria));
addrcriteria.ai_family = AF_UNSPEC;
addrcriteria.ai_socktype = SOCK_DGRAM;
addrcriteria.ai_protocol = IPPROTO_UDP;
addrcriteria.ai_flags |= AI_NUMERICHOST;
struct addrinfo *multicastaddr;
int rnval = getaddrinfo(multicastipstring, service, &addrcriteria, &multicastaddr);
int sock = socket(multicastaddr->ai_family, multicastaddr->ai_socktype, multicastaddr->ai_protocol);
u_char mcttl = (u_char)multicastttl;
setsockopt(sock, IPPOTO_IP, IP_MULTICAST_TTL, &mcttl, sizeof(mcttl));
while(1){
ssize_t numbytes = sendto(sock, sending, sendstringlen, 0, multicastaddr->ai_addr, multicastaddr->ai_addrlen);
sleep(3);
}


