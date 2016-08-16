#include "head.h"
int main()
{
int h;
h = fork();
if(h > 0)
printf("parents %d", h);
else printf("child %d\n", h);
}
