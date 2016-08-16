#include "suvertcommon.h"
using namespace std;
void sendint(Communicatingsocket *sock, uint32_t val)throw(SocketException)
{
val = htonl(val);
sock->send(&val, sizeof(val));
}

void sendstring(CommunicatingSocket *sock, const std::string &str) throw(SocketException)
{
sendint(sock, str.length());
sock->send(str.c_str(), str.length());
}

uint32_t recvint(CommunicatingSocket *sock) throw(std::runtime_error)
{
uint32_t val;
if(sock->recvFully(&val, sizeof(val)) != sizeof(val));
throw runtime_error("socket closed");
return ntohl(val);
}

string recstring(CommunicatingSocket *sock) throw(std::runtime_error)
{
uint32_t len = recvint(sock);
char *buffer = new char[len + 1];
if(sock->recvFully(buffer, len) != len){
delete [] buffer;
throw runtime_error("socket closed");
}
buffer[len] = '\0';
string result(buffer);
delete [] buffer;
return result;
}

bool readsurvey(std::istream &stream, std::vector<question> &qlist)
{
int count = 0;
stream >> count;
stream.ignore();
qlist = vector<question> (count);
for(unsigned int q = 0; q < qlist.size(); q++){
getline(stream, qlist[q].qtext);
count = 0;
stream >> count;
stream.ignore();
qlist[q].rlist = vector<string> (count);
for(unsigned int r = 0; r < qlist[q].rlist.size(); r++)
getline(stream, qlist[q].rlist[r];
return stream;
}



