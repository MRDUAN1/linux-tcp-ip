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

	/* �������˿�ʼ����sockfd������ */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	printf("hello %d\n", sockfd);
	addfd(fd, sockfd);
	
	
	/* ����������� sockaddr�ṹ */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); // ��ʼ��,��0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (���������ϵ�long����ת��Ϊ�����ϵ�long����)���κ�����ͨ��  //INADDR_ANY ��ʾ���Խ�������IP��ַ�����ݣ����󶨵����е�IP
	//server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //���ڰ󶨵�һ���̶�IP,inet_addr���ڰ����ּӸ�ʽ��ipת��Ϊ����ip
	server_addr.sin_port = htons(portnumber);
	sin_size=sizeof(struct sockaddr_in);
	/* ����sockfd��������IP��ַ */ 
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
	
	/* �����������ӵ����ͻ����� */ 
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

	/* ����ͨѶ */ 
	close(sockfd); 
	exit(0); 
} 
