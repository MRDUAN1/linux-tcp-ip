void handletcpclient(int clnsock)
{
char buffer[BUFFSIZE];
ssize_t numberbyterec = recv(clnsock, buffer, BUFFSIZE, 0);
if(numberbyte < 0)
fputs("failed rec", stdout);
while(numberbyterec > 0)
{
ssize_t numberbytesent = send(clnsock, buffer, numberbyterec, 0);
if(numberbytesent != numberbyterec)
fputs("failed sent", stdout);
numberbyterec = recv(clnsock, buffer, BUFFSIZE, 0);
if(numberbyterec < 0)
fputs("failed rec", stdout);
}
close(clnsock);
}



