#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define portnumber 4444

int main(int argc, char *argv[]) 
{ 
	int sockfd; 
	int n;

	fd_set rest, wset;
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
	int flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
	/* �ͻ�����������˵����� */ 
	bzero(&server_addr,sizeof(server_addr)); // ��ʼ��,��0
	server_addr.sin_family=AF_INET;          // IPV4
	server_addr.sin_port=htons(portnumber);  // (���������ϵ�short����ת��Ϊ�����ϵ�short����)�˿ں�
	server_addr.sin_addr=*((struct in_addr *)host->h_addr); // IP��ַ
	
	/* �ͻ��������������� */ 
	while(n = connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) < 0) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		sleep(1); 
	} 
	if(n == 0)
	{
	printf("the connectioned....\n");
	goto done;
	}
	done:{
	
	//FD_ZERO(&rest);
	FD_ZERO(&wset);
	FD_SET(sockfd, &wset);
	//FD_SET(sockfd, &rest);
	select(sockfd + 1, NULL, &wset, NULL, NULL);
	printf("hello world\n");
	if(FD_ISSET(sockfd, &wset))
	{
	/* ���ӳɹ��� */ 
	printf("Please input char:\n");
	 
	/* �������� */
	fgets(buffer,1024,stdin); 
	write(sockfd,buffer,strlen(buffer)); }

	/* ����ͨѶ */ 
	close(sockfd); 
	exit(0);} 
} 
