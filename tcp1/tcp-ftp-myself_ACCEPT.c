#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#define port 4444
void *function(void *arg)
{

int num;
int ret;
int i;
struct sockaddr_in sa;
int len = sizeof(sa);
char buffer[1024];
char buf[20];

struct epoll_event ev, events[20];
int fd = epoll_create(10);
int accept_fir = (int)arg;

if(!getpeername(accept_fir, (struct sockaddr *)&sa, &len))
{
printf("either ip: %s\n", inet_ntoa(sa.sin_addr));
printf("either port : %d\n", ntohs(sa.sin_port));
}

while(1){

epoll_ctl(fd, EPOLL_CTL_ADD, accept_fir, &ev);
ret = epoll_wait(fd, events, 20, 500);

for(i = 0; i < ret; i++)
{

printf("now is read\n"); 
num = read(accept_fir, buffer, 1024);
if(!strcmp(buffer, "exit\n"))
{
printf("connection over from %s\n", inet_ntoa(sa.sin_addr));
goto done;
}
if(num == 0){printf("sometjing wrong\n");goto done;}
buffer[num]='\0';
printf("nbytes = %d\n",num);
printf("Server received  %s from %s::%d\n",buffer, inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
}
else if(FD_ISSET(0, &readset))
{
printf("now you can write\n");
fputs("print your data\n", stdout);
fgets(buffer, 100, stdin);
num = write(accept_fir, buffer, sizeof(buffer));
}
else if(FD_ISSET(accept_fir, &erronset)){
printf("something wrong in sockfd\n");
goto done;}
}


done:
close(accept_fir);
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
//int flags = fcntl(sock_fir, F_GETFL, 0);
//fcntl(sock_fir, F_SETFL, flags | O_NONBLOCK);
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
fcntl(sock_sec, F_SETFD, O_NONBLOCK);

if(sock_sec == -1){printf("something wrong in accept");exit(0);}
fprintf(stderr,"Server get connection from %s\n",inet_ntoa(sockaddr_sec.sin_addr));
pthread_create(&pid, NULL, function, (void*)sock_sec);
//pthread_join(pid, NULL);



}
close(sock_fir);

return 0;
}




