#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#define portnumber 4444
int main(int argc, char *argv[])
{
assert(argc == 2);
char *host = argv[1];
struct hostent *hostinfo = gethostbyname( host );
assert(hostinfo);
struct servent *servinfo = getservbyname("daytime", "tcp");
assert(servinfo);
printf("daytimeport port is %d\n", ntohs(servinfo->s_port));
struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_port = servinfo->s_port;
address.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
char buffer[128];
result = read(sockfd, buffer, sizeof(buffer));
assert(result > 0);
buffer[result] = '\0';
printf("the day time is :%s", buffer);
close(sockfd);
return 0;
}


