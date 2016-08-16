int main(int argc, char *argv[])
{
long timeout = atol(argv[1]);
int noports = argc - 2;
int servsock[noports];
int maxdescription = -1;
for(int port = 0; port < noports; port++)
{
servsock[port] = setuptcpserversocket(argv[port + 2]);
if(servsock[port] > maxdescription)
maxdescription = servsock[port];
}
puts("starting server : hit return ");
bool running = true;
fd_set sockset;
while(running)
{
FD_ZERO(&sockset);
FD_SET(STDIN_FILENO, &sockset);
for(int port = 0; port < noports; port++)
{
FD_SET(servsock[port], &sockset);
struct timeval seltimeout;
seltimeout.tv_sec = timeout;
seltimeout.tv_usec = 0;
if(selet(maxdescription + 1, &sockset, NULL, NULL, &seltimeout) == 0)
printf("no echo %ld secs....server\n", timeout);
else{
if(FD_ISSET(0, &sockset)){
puts("shutting down server");
getchar();
running = false;
}
for(int port = 0; port < noports; port++)
if(FD_ISSET(servsock[port], &sockset)){
printf("request on port %d:", port);
handletcpclient(accepttcpconnection(servsock[port]));
}
}
}
for(int port = 0; port < noports; port++)
close(servsock[port]);
exit(0);
}




