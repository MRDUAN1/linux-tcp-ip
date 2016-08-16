#include "head.h"
static int nchildren;
static pid_t *pids;

int main(int argc, char **argv)
{
int listenfd, i;
void sig_int(int);
struct sigaction handler;
handler.sa_handler = sig_int;
sigfillset(&handler.sa_mask);
sigaction(SIGINT, &sig_int, 0);
handler.sa_flags = 0;
socklen_t addrlen;
void sig_int(int);
pid_t child_make(int, int, int);
listenfd = tcp_listen(NULL, argv[1], &addrlen);
nchildren = atoi(argv[argc - 1]);
pids = calloc(nchildren, sizeof(pid_t));
for(i = 0; i < nchildren; i++)
pids[i] = child_make(i, listenfd, addrlen);
for(;;)
pause();
}

void sig_int(int signo)
{
int i;
for(i = 0; i < nchildren; i++)
kill(pids[i], SIGTERM);
while(wait(NULL) > 0);
if(errno != ECHILD)printf("somet\n");
exit(0);
}

pid_t child_make(int i, int listenfd, int addrlen)
{
pid_t pid;
void child_main(int, int, int);
if((pid = fork() ) > 0)
return (pid);
child_main(i, listenfd, addrlen);
}

void child_main(int i, int listenfd, int addrlen)
{
int connfd;
void web_child(int);
socklen_t chilen;
struct sockaddr *cliaddr;
cliaddr = (struct sockaddr*)malloc(sizeof(cliaddr));
printf("child %ld starting\n", (long)getpid());
while(1){
chilen = addrlen;
connfd = accept(listenfd, cliaddr, &chilen);
web_child(connfd);
close(connfd);
}
}

void web_child(int connfd)
{
int nbytes;
char buffer[1024];
if((nbytes=read(connfd,buffer,1024))==-1) 
{ 
	fprintf(stderr,"Read Error:%s\n",strerror(errno)); 
	exit(1); 
} 
		
buffer[nbytes]='\0';
printf("nbytes = %d\n",nbytes);
printf("Server received %d %s\n",getpid(), buffer);
}
		















