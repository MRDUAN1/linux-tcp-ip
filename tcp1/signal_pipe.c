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
#include <pthread.h>
#define MAX 1024
static int pipefd[2];
int setnonblocking(int fd)
{
int old_option = fcntl(fd, F_GETFL);
int new_option = old_option | O_NONBLOCK;
fcntl(fd, F_SETFL, new_option);
return old_option;}

void addfd(int epollfd, int fd)
{
epoll_event event;
event.data,fd = fd;
event.events = EPOLLIN | EPOLLET;
epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
setnonblocking(fd);
}
void sig_handler(int sig){
int save_errno = errno;
int msg = sig;
send(pipefd[1], (char *)&msg, 1, 0);
errno = save_errno
}
void addsig(int sig)
{
struct sigaction sa;
memset(&sa, '\0', sizeof(sa));
sa.sa_handler = sig_handler;
sa_flags |= SA_RESTART;
sigfillset(&sa.sa_mask);
assert(sigaction(sig, &sa, NULL));xx
}

int main(int argc, char *argv[]) 
{ 
	int sockfd,new_fd; 
	struct sockaddr_in name;
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr; 
	int sin_size; 
	int nbytes;
	char buffer[1024];
	

	/* 服务器端开始建立sockfd描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	/* 服务器端填充 sockaddr结构 */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); // 初始化,置0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (将本机器上的long数据转化为网络上的long数据)和任何主机通信  //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	//server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	server_addr.sin_port=htons(0);         // (将本机器上的short数据转化为网络上的short数据)端口号
	
	/* 捆绑sockfd描述符到IP地址 */ 
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	socklen_t namelen = sizeof(name);
	getsockname(sockfd, (struct sockaddr*)&name, &namelen);
	int port1 = ntohs(name.sin_port);
	printf("the port is %d\n", port1);

	/* 设置允许连接的最大客户端数 */ 
	if(listen(sockfd,5)==-1) 
	{ 
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	epoll_event events[MAX];
	int epollfd = epoll_create(5);
	assert(epollfd != -1);
	addfd(epollfd, sockfd);
	int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
	assert(ret != -1);
	setnoblocking(pipefd[1]);
	addfd(epollfd, pipefd[0]);
	addsig(SIGHUP);
	addsig(SIGCHLD);
	addsig(SIGTERM);
	addsig(SIGINT);
	bool stop_server = false;
	while( !stop_srver){
	int number = epoll_wait(epollfd, events, MAX, -1);	
	if(number < 0) && (errno != EINTR))
	{
		printf("epoll failure");
		break;
	}
	for(i = 0; i < number; i++)
	{
	int sock = events[i].data.fd;
	if(sock == sockfd)
	{
	struct sockaddr_in client_address;
	socklen_t client_addrlength = sizeof(client_address);
	int connfd = accept(sock, (struct sockaddr*)&client_address, &client_addrlength);
	addfd(epollfd, connfd);
	}
	else if((sock == pipefd[0] && (events[i].events & EPOLLIN))
	{
	int sig;
	char signals[1024];
	ret = recv(pipefd[0], signals, sizeof(signals), 0);
	if(ret == -1)continue;
	else if(ret == 0)continue;
	else{
	int i;
	for(int i = 0; i < ret; i++)
	{
	switch(signals[i])
	case SIGCHID:
	case SIGHUP:
	{
	continue;
	}
	case SIGTERM:
	case SIGINT:
	{
	stop_server = true;
	}
	}
}
}
}
else
{}
}
}
printf("close fds\n");
close(sockfd);
close(pipefd[0]);
close(pipefd[1]);
return 0;
}
	

