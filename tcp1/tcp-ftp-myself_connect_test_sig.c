#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <pthread.h>
#define port 3333
void *function(void *arg)
{
int num;
char buffer[1024];
int acept = (int)arg;
num = read(arg, buffer, 1024);
buffer[num]='\0';
printf("nbytes = %d\n",num);
printf("Server received %s\n",buffer);
close(acept);
pthread_exit(0);

}
int main()
{

int n, sin_size;
int sock_fir, sock_sec;
pthread_t pid;
struct sockaddr_in sockaddr_fir; 
struct sockaddr_in sockaddr_sec;
bzero(&sockaddr_fir, sizeof(struct sockaddr_in));
sockaddr_fir.sin_family = AF_INET;
sockaddr_fir.sin_port = htons(port);
sockaddr_fir.sin_addr.s_addr = htonl(INADDR_ANY);
sock_fir = socket(AF_INET, SOCK_STREAM, 0);

setsockopt(sock_fir,SOL_SOCKET,SO_REUSEADDR,&n,sizeof(int));
if(bind(sock_fir, (struct sockaddr *)&sockaddr_fir, sizeof(struct sockaddr)) == -1)
{
printf("something wrong in bind");
exit(0);
}

if(listen(sock_fir, 5) == -1)
{printf("something wrong in listen");
exit(0);
}

while(1)
{
sin_size=sizeof(struct sockaddr_in);
sock_sec = accept(sock_fir, (struct sockaddr*)(&sockaddr_sec), &sin_size);
printf("hello world\n");
if(sock_sec == -1){printf("something wrong in accept");exit(0);}
fprintf(stderr,"Server get connection from %s\n",inet_ntoa(sockaddr_sec.sin_addr));
pthread_create(&pid, NULL, function, (void*)sock_sec);


///close(sock_sec);

}
close(sock_fir);

return 0;
}



