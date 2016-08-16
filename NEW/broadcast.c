#include "head.h"
int main(int argc, char **argv)
{
in_port_t port = htons((in_port_t) atoi(argv[2]));
struct sockaddr_storage deststorage;
bzero(&deststorage, sizeof(deststorage));
size_t addrsize = 0;
if(argv[1][0] == '4'){
struct sockaddr_in *destadder4 = (tsruct sockaddr_in *)&deststorage;
destadder4->sin_family = AF_INET;
destadder4->sin_port = port;
destadder4->sin_addr.s_addr = INADDR_BROADCAST;
addrsize = sizeof(struct sockaddr_in);
}
struct sockaddr *destaddress = (struct sockaddr *)&deststorage;
size_t msglen = strlen(argv[3]);
int sock = socket(destaddress->ai_family, SOCK_DGRAM, IPPOTO_UDP);
int broadcastperm = 1;
setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastperm, sizeof(broadcastperm));
while(1){
ssize_t numbytes = sendto(sock, argv[3], msglen, 0, destaddress, addrsize);
sleep(3);
}
}

