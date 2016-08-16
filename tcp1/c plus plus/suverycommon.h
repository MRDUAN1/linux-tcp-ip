#ifndef __SURVYRCOMMOM_H__
#define __SURVYRCOMMOM_H__
#include <string>
#include <vector>
const in_port_t survey_port = 12543;
void sendint(Communicatingsocket *sock, uint32_t val)throw(SocketException);
void sendstring(CommunicatingSocket *sock, const std::string &str) throw(SocketException);
uint32_t recvint(CommunicatingSocket *sock) throw(std::runtime_error);
std::string recstring(CommunicatingSocket *sock) throw(std::runtime_error);
struct question{
std::string qtext;
std::vector<std::string> rlist;
};

bool readsurvey(std::istream &stream, std::vector<question> &qlist);
#endif
