#include "head.h"
int main()
{
int s[2];
int w, r;
char *string = "this is a test string";

socketpair(AF_UNIX, SOCK_STREAM, 0, s);
int n = fork();
if(n == 0)
{
printf("i am child\n");
close(s[0]);
write(s[1], "hello\n", sizeof("hello\n"));
exit(0);
}
else if(n > 0)
{
close(s[1]);
char buffer[1024];
fd_set pipefd;
FD_ZERO(&pipefd);
FD_SET(s[0], &pipefd);
int ret = select(100, &pipefd, NULL, NULL, NULL);

if(FD_ISSET(s[0], &pipefd))
{
read(s[0], buffer, 20);
printf("dfff%shhh", buffer);
}
}
}


















