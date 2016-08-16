#include "public.h"
#define BUF_SIZE 30
int main()
{
int s[2];
int w, r;
char *string = "this is a test string";
char *buf = (char *)calloc(1, BUF_SIZE);
socketpair(AF_UNIX, SOCK_STREAM, 0, s);
w = write(s[0], string, strlen(string));
r = read(s[1], buf, BUF_SIZE);
printf("reading from %s\n", buf);
if(read = read(s[0], buf, BUF_SIZE)) == -1){
printf("sometime has wrong%s\n", strerror(errno));
exit(-1);
}
printf("read from s0 error%s\n", sterror(errno));
exit(-1);

