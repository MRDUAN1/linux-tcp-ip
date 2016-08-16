#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <signal.h>
#define portnumber 4444
static void connect_alarm(int hp)
{
return 0;};
int main(int argc, char *argv[]) 
{
	struct sigaction handler;
	handler.sa_handler = connect_alarm;
	sigfillset(&handler.sa_mask);
	handler.sa_flags = 0;
	
 	int n;
	//Sigfunc *sigfunc;
	int sockfd; 
	char buffer[1024]; 
	struct sockaddr_in server_addr; 
	struct hostent *host; 

        /* 使用hostname查询host 名字 */
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

	/* 客户程序开始建立 sockfd描述符 */ 
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:Internet;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 

	/* 客户程序填充服务端的资料 */ 
	bzero(&server_addr,sizeof(server_addr)); // 初始化,置0
	server_addr.sin_family=AF_INET;          // IPV4
	server_addr.sin_port=htons(portnumber);  // (将本机器上的short数据转化为网络上的short数据)端口号
	server_addr.sin_addr=*((struct in_addr *)host->h_addr); // IP地址
	sigaction(SIGALRM, &connect_alarm, 0);
	/* 客户程序发起连接请求 */ 
	alarm(5);
	if((n = connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))) < 0) 
	{ close(sockfd);
	if(errno == EINTR) errno = ETIMEDOUT;
	} 
	
	/* 连接成功了 */ 
	printf("Please input char:\n");
	
	/* 发送数据 */
	fgets(buffer,1024,stdin); 
	write(sockfd,buffer,strlen(buffer)); 

	/* 结束通讯 */ 
	close(sockfd); 
	exit(0); 
} 
