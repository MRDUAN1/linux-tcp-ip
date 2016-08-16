#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <fcntl.h>
#include <sys/epoll.h>
#include <unistd.h>

#define portnumber 4444
int setnonblocking(int fd)
{
int old_option = fcntl(fd, F_GETFL);
int new_option = old_option | O_NONBLOCK;
fcntl(fd, F_SETFL, new_option);
return old_option;}

void addfd(int epollfd, int fd)
{
struct epoll_event event;
event.data.fd = fd;
event.events = EPOLLIN | EPOLLET;
epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
//setnonblocking(fd);
}
int main(int argc, char *argv[]) 
{ 
	int sockfd,new_fd, nfds, other_socket; 
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr; 
	int sin_size; 
	int nbytes;
	char buffer[1024];
	int i = 0;
	struct epoll_event ev, events[1024];
	int fd = epoll_create(256);

	/* 服务器端开始建立sockfd描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	printf("hello %d\n", sockfd);
	addfd(fd, sockfd);
	
	
	/* 服务器端填充 sockaddr结构 */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); // 初始化,置0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (将本机器上的long数据转化为网络上的long数据)和任何主机通信  //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	//server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	server_addr.sin_port = htons(portnumber);
	sin_size=sizeof(struct sockaddr_in);
	/* 捆绑sockfd描述符到IP地址 */ 
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	
	/* 设置允许连接的最大客户端数 */ 
	if(listen(sockfd,5)==-1) 
	{ 
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	
	
	while(1) 
	{ printf("hello\n");
		nfds = epoll_wait(fd, events, 1024, -1);
		printf("hello accept\n");
		printf("ARM\n");
		for(i = 0; i < nfds; i++){
		if(events[i].data.fd == sockfd){
		struct sockaddr_in client_address;
		socklen_t client_addre = sizeof(client_addre);
		new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addre);
		
		addfd(fd, new_fd);}
		else if(events[i].events&EPOLLIN){
		other_socket = events[i].data.fd;
		int n = read(other_socket, buffer, 1024);
		ev.data.fd = other_socket;
		ev.events = EPOLLOUT | EPOLLET;
		epoll_ctl(fd, EPOLL_CTL_MOD, other_socket, &ev);}
		else if(events[i].events&EPOLLOUT)
		{
		other_socket = events[i].data.fd;
		write(other_socket, buffer, 1024);
		ev.data.fd = other_socket;
		ev.events = EPOLLIN | EPOLLET;
		epoll_ctl(fd, EPOLL_CTL_MOD, other_socket, &ev);
		
		}
		
		
		
		 
		
	} }

	/* 结束通讯 */ 
	close(sockfd); 
	exit(0); 
} 
