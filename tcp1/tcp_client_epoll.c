#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <unistd.h>
#define portnumber 4444

int main(int argc, char *argv[]) 
{ 
	int sockfd; 
	int n, epoll_n, i;
	struct epoll_event ev, events[20];
	int fd = epoll_create(20);
	char buffer[1024]; 
	struct sockaddr_in server_addr; 
	struct hostent *host; 

        /* ʹ��hostname��ѯhost ���� */
	if(argc!=2) 
	{ 
		fprintf(stderr,"Usage:%s hostname \a\n",argv[0]); 
		exit(1); 
	} 

	if((host=gethostbyname(argv[1]))==NULL) 
	{ 
		fprintf(stderr,"Gethostname error\n"); 
		exit(1); 
	} 

	/* �ͻ�����ʼ���� sockfd������ */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:Internet;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 

	/* �ͻ�����������˵����� */ 
	bzero(&server_addr,sizeof(server_addr)); // ��ʼ��,��0
	server_addr.sin_family=AF_INET;          // IPV4
	server_addr.sin_port=htons(portnumber);  // (���������ϵ�short����ת��Ϊ�����ϵ�short����)�˿ں�
	server_addr.sin_addr=*((struct in_addr *)host->h_addr); // IP��ַ
	int flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
	ev.events = (uint32_t)(EPOLLIN | EPOLLOUT | EPOLLET);
	epoll_ctl(fd, EPOLL_CTL_ADD, sockfd, &ev);
	
	/* �ͻ��������������� */ 
	while(n = connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) < 0) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		
	}
	if(n == 0){

	/* ���ӳɹ��� */ 
	printf("Please input char:\n");}
	while(1)
	{
	//printf("while in\n");
	epoll_n = epoll_wait(fd, &ev, 1, -1);
	printf("the epoll_n : %d\n", epoll_n);
	if(epoll_n < 0) continue;
	/*for(i = 0; i < epoll_n; i++)
	{
	if(events[i].data.fd == sockfd)
	{*/
	
	/* �������� */
	fgets(buffer,1024,stdin); 
	write(sockfd,buffer,strlen(buffer)); 
	printf("hello\n");
	/* ����
ͨѶ */ 
	close(sockfd); }
	exit(0); 
} 
