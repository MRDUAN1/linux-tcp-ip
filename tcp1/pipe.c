#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
int pfds[2];
if(pipe(pfds) == 0){
if(fork() == 0){
close(stdout);
dup2(pfds[1], stdout);
close(pfds[0]);
execlp("ls", "ls", "-l", NULL);
}
else{
close(stdin);
dup2(pfds[0], stdin);
close(pfds[1]);
execlp("wc", "wc", "-l", NULL);
}
return 0;
}
}
