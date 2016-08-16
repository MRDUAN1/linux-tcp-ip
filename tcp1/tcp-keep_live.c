int anetkeepalive(char *err, int fd, int interval)
{
int val = 1;
if(setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) == -1){
fputs("something wrong");
return 0;}
val = interval;
setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &val, sizeof(val));

