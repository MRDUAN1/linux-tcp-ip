#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#define portnumber 4444

int main(int argc, char *argv[]) 
{ 
	int sockfd,new_fd; 
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr; 
	int sin_size; 
	int nbytes;
	char buffer[1024];
	

	/* �������˿�ʼ����sockfd������ */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 

	/* ����������� sockaddr�ṹ */ 
	bzero(&server_addr,sizeof(struct sockaddr_in)); // ��ʼ��,��0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (���������ϵ�long����ת��Ϊ�����ϵ�long����)���κ�����ͨ��  //INADDR_ANY ��ʾ���Խ�������IP��ַ�����ݣ����󶨵����е�IP
	//server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //���ڰ󶨵�һ���̶�IP,inet_addr���ڰ����ּӸ�ʽ��ipת��Ϊ����ip
	server_addr.sin_port=htons(portnumber); 
	int keeplive = 1;
        // (���������ϵ�short����ת��Ϊ�����ϵ�short����)�˿ں�
	setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,(void *)&keeplive,sizeof(keeplive));
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
	{ 
		/* ����������,ֱ���ͻ����������� */ 
		sin_size=sizeof(struct sockaddr_in); 
		if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1) 
		{ 
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
			exit(1); 
		} 
		fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr)); // �������ַת����.�ַ���
		int opt;
		socklen_t len = sizeof(int);
		getsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (char *)&opt, &len);
		printf("connection for %d\n", opt);
		send(new_fd, "hello\n", 50, 0);
		while(1){
		if((nbytes=read(new_fd,buffer,1024))==-1) 
		{ 
			fprintf(stderr,"Read Error:%s\n",strerror(errno)); 
			exit(1); 
		} 
		if(!strcmp(buffer, "exit\n"))break;
		buffer[nbytes]='\0';
		printf("nbytes = %d\n",nbytes);
		printf("Server received %s\n",buffer);
		memset(buffer,0, sizeof(buffer));}
		
		
		/* ���ͨѶ�Ѿ����� */ 
		close(new_fd); 
		/* ѭ����һ�� */ 
	} 

	/* ����ͨѶ */ 
	close(sockfd); 
	exit(0); 
} 