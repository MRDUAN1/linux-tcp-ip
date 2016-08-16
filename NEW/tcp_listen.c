#include "head.h"
int tcp_listen(int portnumber){
struct sockaddr_in server_addr; 
int sin_size; 
int nbytes;
char buffer[1024];
if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
{ 
	fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
	exit(1); 
} 
bzero(&server_addr,sizeof(struct sockaddr_in)); // 初始化,置0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  // (将本机器上的long数据转化为网络上的long数据)和任何主机通信  //INADDR_ANY 表示可以接收任意IP地址的数据，即绑定到所有的IP
	//server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");  //用于绑定到一个固定IP,inet_addr用于把数字加格式的ip转化为整形ip
	server_addr.sin_port=htons(portnumber);         // (将本机器上的short数据转化为网络上的short数据)端口号
	
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
}

