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

#define portnumber 4444

int main(int argc, char *argv[]) 
{ 
	int sockfd; 
	int num;
	int ret;
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
	
	/* �ͻ��������������� */ 
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 
	//fcntl(sockfd, F_SETFD, O_NONBLOCK);
	
	/* ���ӳɹ��� */ 
	printf("Please input char:\n");
	
	while(1){
fd_set readset, writeset, erronset;
	FD_SET(sockfd, &readset);
	//FD_SET(sockfd, &writeset);
	FD_SET(sockfd, &erronset);
	FD_SET(0, &readset);
ret = select(sockfd + 1, &readset, &writeset, &erronset, NULL);
if(ret == 0) continue;
if(FD_ISSET(sockfd, &readset)){ 
printf("now is read\n"); 
num = read(sockfd, buffer, sizeof(buffer) + 1);
if(num == 0){printf("sometjing wrong\n");exit(0);}
buffer[num]='\0';
printf("nbytes = %d\n",num);
printf("client received %s\n",buffer);
FD_ZERO(&readset);
}
else if(FD_ISSET(0, &readset))
{
printf("now you can write\n");
fputs("print your data\n", stdout);
fgets(buffer, 100, stdin);
num = write(sockfd, buffer, sizeof(buffer));
}
else if(FD_ISSET(sockfd, &erronset)){
printf("something wrong in sockfd\n");
close(sockfd);
exit(0);
}
FD_ZERO(&readset);
FD_ZERO(&writeset);
FD_ZERO(&erronset);
}

	
	/* ����ͨѶ */ 
	close(sockfd); 
	exit(0); 
} 
