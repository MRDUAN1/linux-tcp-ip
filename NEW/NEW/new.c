#include "head.h"
int main()
{
//int sockets[2];
//socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
int n, sin_size;
socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
int sock_fir, sock_sec;
pthread_t pid, pid_master;
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
calloc(20, sizeof(pthread_t));
for(i = 0; i < 20; i++)
child_make(&pthread[i], sock_fir);
for(;;) pause();
}

int  child_make(pthread_t * id, int sock_fir)
{
int i
i = pthread_create(id, NULL, child_main, (void *)sock_fir);
if(i != 0) {printf("wrong int thread\n"); exit(0); }
}

void *child_main(void *arg)
{
int connfd;
int accept_fir = (int)arg;
socklen_t childen;
struct sockaddr *cliaddr;
int sin_size = sizeof(cliaddr);
printf("child %ld starting ", pthread_self());
struct sockaddr_in sa;
while(1){
connfd = accept(accept_fir, cliaddr, &sin_size);
if(!getpeername(accept_fir, (struct sockaddr *)&sa, &len))
{
printf("either ip: %s\n", inet_ntoa(sa.sin_addr));
printf("either port : %d\n", ntohs(sa.sin_port));
}

while(1){
FD_ZERO(&readset);
FD_ZERO(&writeset);

FD_SET(accept_fir, &readset);
//FD_SET(accept_fir, &writeset);
FD_SET(0, &readset);
FD_SET(accept_fir, &erronset);
//FD_SET(sockets[0], &readset);
int ret = select(accept_fir + 1, &readset, &writeset, &erronset, NULL);
if(ret == 0) continue;
if(FD_ISSET(accept_fir, &readset)){ 
printf("now is read\n"); 
num = read(accept_fir, buffer, 1024);
if(!strcmp(buffer, "exit\n"))
{
printf("connection over from %s\n", inet_ntoa(sa.sin_addr));
goto done;
}
if(!strcmp(buffer, "i want a master\n"))
{pthread_mutex_lock(&mutex);
pthread_cond_signal(&mycond);
pthread_mutex_unlock(&mutex);
}
if(num == 0){printf("sometjing wrong\n");goto done;}
buffer[num]='\0';
printf("nbytes = %d\n",num);
printf("Server received  %s from %s::%d\n",buffer, inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
continue;
//send_two()
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
/*else if(FD_ISSET(sockets[0], &readset))
{
num = read(sockets[0], buffer, 1024);
printf("the master take to %s\n", buffer);
}*/


done:
close(accept_fir);
pthread_exit(0);
}}
















