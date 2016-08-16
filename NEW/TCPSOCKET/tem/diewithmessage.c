#include <stdio.h>
#include <stdlib.h>
void dieusermessage(const char *msg, const char *detail){
fputs(msg, stderr);
puts(": ", stderr);
fputs(detail, stderr);
fputc('\n', stderr);
exit(1);
}

void diesysmessage(const char *msg){
perror(msg);
exit(1);
}
