#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
int i = 0;
int dst;
try{
int char[2];
TCPServerSocket servsock(9431);
for(;;){
i++;
TCPSocket *sock = servsock.accept();
uint32_t val;
if(sock->recvFully(&val, sizeof(val)) == sizeof(val)){
val = ntohl(val);
if(i != 2){
char[1] = val;
continue;}
else {
char[2] = val;
dst = char[1] + char[2];
dst = htonl(dst);
sock->send(&val, sizeof(val));
}
delete sock;
}catch(SocketException &e){
cerr << e.what() << endl;
}
return 0;
}


