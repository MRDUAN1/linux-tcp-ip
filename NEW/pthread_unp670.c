#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
void thread_make(int i){
void *thread_main(void *);
pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *)i);
return ;
}

void *thread_main(void *arg)
{
int connfd;
void web_child(int);
socklen_t chilen;
struct sockaddr *cliaddr;
cliaddr = 
typedef struct {
pthread_t thread_tid;
long thread_count;
}Thread;
Thread *tptr;
pthread_mutex_t mutex;

#define MY_PORT 3333

int main(int argc ,char **argv)
{
 int listen_fd,accept_fd;
 struct sockaddr_in     client_addr;
 int n;
 
 if((listen_fd=socket(AF_INET,SOCK_STREAM,0))<0)
  {
        printf("Socket Error:%s\n\a",strerror(errno));
        exit(1);
  }
 
 bzero(&client_addr,sizeof(struct sockaddr_in));
 client_addr.sin_family=AF_INET;
 client_addr.sin_port=htons(MY_PORT);
 client_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 n=1;
 /* 如果服务器终止后,服务器可以第二次快速启动而不用等待一段时间  */
 setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&n,sizeof(int));
 if(bind(listen_fd,(struct sockaddr *)&client_addr,sizeof(client_addr))<0)
  {
        printf("Bind Error:%s\n\a",strerror(errno));
        exit(1);
  }
  listen(listen_fd,5);
int nthreads = atoi(argv[argc - 1]);
tptr = calloc(nthreads, sizeof(Thread));
for(i = 0; i < nthreads; i++)
thread_make(i);

