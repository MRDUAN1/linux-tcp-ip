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
#include <arpa/inet.h>
#define port 4444
int i;
static int sockets[2];
//socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;
/*typedef struct pthread_table{
struct sockaddr_storage localaddr;
struct pthread_table *next;
}*/

make_chid(int client[i])
{







void *function_master(void *arg)
{

char buffer[1024] = {'\0'};
pthread_mutex_lock(&mutex2);
pthread_cond_wait(&mycond, &mutex2);
pthread_mutex_unlock(&mutex2);
printf(" i am master\n");
//fgets(buffer, 1024, 0);
scanf("%s", buffer);
write(sockets[1], buffer, sizeof(buffer));
}
void *function(void *arg)
{
//#define "accept" "accept_fir"
int num;
int ret;
struct sockaddr_in sa;
int len = sizeof(sa);
char buffer[1024];
char buf[20];
fd_set readset, writeset, erronset;


int accept_fir = (int)arg;
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
FD_SET(sockets[0], &readset);
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
continue;
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
else if(FD_ISSET(sockets[0], &readset))
{
num = read(sockets[0], buffer, 1024);
printf("the master take to %s\n", buffer);
}


done:
close(accept_fir);
pthread_exit(0);
}}

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
pthread_create(&pid_master, NULL, function_master, NULL);
for(i = 0; i < 20; i++)
make_chid(client[i]);
close(sock_fir);

 
return 0;
}



