int accepttcpconnection(int servsock)
{
struct sockaddr_stroage clntaddr;
socklen_t clnaddrlen = sizeof(clnaddr);
int clnsock = accept(servsock, (struct sockaddr *)&clnaddr, &clnaddrlen);
if(clnsock < 0)
diesystemmessage("accept() failed");
fputs("handling client", stdout);
printsockaddress((struct sockaddr *)&clnaddr, stdout);
fputc('\n', stdout);
return clnsock;
}
