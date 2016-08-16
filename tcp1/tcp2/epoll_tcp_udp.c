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
#include <assert.h>
#define portnumber 4444

void setnonblocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);
	if (opts<0)
	{
		perror("fcntl(sock,GETFL)");
		exit(1);
	}
	opts = opts | O_NONBLOCK;
	if (fcntl(sock, F_SETFL, opts)<0)
	{
		perror("fcntl(sock,SETFL,opts)");
		exit(1);
	}
}

void addfd(int epollfd, int fd)
{
struct epoll_event event;
event.data.fd = fd;
event.events = EPOLLIN | EPOLLET;
epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
setnonblocking(fd);
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
	assert(sockfd >= 0);
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
	bzero(&server_addr,sizeof(struct sockaddr_in)); // 初始化,置0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (将本机器上的long数据转化为网络上的long数据)和任何主机通信  //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	//server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	server_addr.sin_port = htons(portnumber);
	sin_size=sizeof(struct sockaddr_in);
	int udpfd = socket(PF_INET, SOCK_DGRAM, 0);
	assert(udpfd >= 0);
	int ret = bind(udpfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	//struct epoll_event events[256];
	int epollfd = epoll_create(5);
	assert(epollfd != -1);
	addfd(epollfd, sockfd);
	addfd(epollfd, udpfd);
	while(1){
	int number = epoll_wait(epollfd, events, 256, -1);
	if(number < 0){printf("epoll failure\n");break;}int i;
	for(i = 0; i < number; i++)
	{
	int sockfd1 = events[i].data.fd;
	if(sockfd1 = sockfd)
	{
	struct sockaddr_in client_address;
	socklen_t client_addre = sizeof(client_addre);
	int connfd = accept(sockfd, (struct sockaddr*)&client_address, &client_addre);
	addfd(epollfd, connfd);
	}
	else if(sockfd1 == udpfd)
	{
	char buf[1024];
	memset(buf, '\0', 1024);
	struct sockaddr_in client_address;
	socklen_t client_addre = sizeof(client_addre);
	ret = recvfrom(udpfd, buf, 1024-1, 0, (struct sockaddr *)&client_address, &client_addre);
	if(ret > 0)sendto(udpfd, buf, 1024-1, 0, (struct sockaddr *)&client_address, client_addre);
	}
	else if(events[i].events & EPOLLIN)
	{
	char buf[1024];
	while(1){
	memset(buf, '\0', 1024);
	ret = recv(sockfd1, buf, 1024-1, 0);
	if(ret < 0)
	{
	if((errno == EAGAIN) || (errno == EWOULDBLOCK))break;
	close(sockfd1);
	break;}
	else if(ret == 0)close(sockfd1);
	else send(sockfd1, buf, ret, 0);
	}}
	else printf("something wrong\n");
	}}
close(sockfd);
return 0;
}
	
