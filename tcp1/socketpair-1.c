#include "public.h"
#define BUF_SIZE 30
int main()
{
int s[2];
int w, r;
char string = "this is a test string";
char *buf = (char *)calloc(1, BUF_SIZE);
pid_t pid;
socketpair(AF_UNIX, SOCK_STREAM, 0, s);
if((pid = fork()) > 0){
printf("parents pid is%d\n", getpid());
close(s[1]);
if((w = write(s[0], string, strlen(string))) == -1)
{
printf("write %s\n", sterror(erron));
exit(-1);
}
else if(pid == 0){
printf("fork child process\n");
printf("child process pid is %d\n", getpid());
close(s[0]);
}else{
printf("something wrong");
exit(-1);}

if((r = read(s[1], buf, BUF_SIZE)) == -1){
printf("pid %d read from socket erron: %s\n", getpid(), strerror(erron));
exit(-1);
}
printf(pid %d read string in same process%s\n", getpid(), buf);
printf("test successued %d\n", getpid());
exit(0);
}

















