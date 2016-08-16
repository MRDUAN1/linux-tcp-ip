#include "head.h"
void server(int readfd, int writefd)
{
int fd;
ssize_t n;
char buffer[1024];
n = read(readfd, buffer, 1024);
buffer[n] = '\0';
if(fd = open(buffer, O_RDONLY) < 0) assert(0);
while(n = read(fd, buffer, 1023) > 0)
write(writefd, buffer, n);
close(fd);
}

void client(int writefd, int readfd)
{
int len;
ssize_t n;
char buffer[1024];
fgets(buffer, 1024, 0);
len = strlen(buffer);
if(buffer[len - 1] == '\n')
len--;
write(writefd, bufeer, len);
while(n = read(readfd, buffer, 1024) > 0)
write(1, buffer, n);
}

int main(){
int pipe1[2], pipe2[2];
pid_t child;
pipe(pipe1[2]);
pipe(pipe2[2]);
if(child = fork() == 0)
{
close(pipe1[1]);
close(pipe2[0]);
server(pipe1[0], pipe2[1]);
exit(0);
}
close(pipe1[0]);
close(pipe2[1]);
client(pipe1[1], pipe2[0]);
waitpid(child, NULL, 0);
exit(0)
;}
