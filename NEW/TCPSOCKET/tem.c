#include "head.h"
#define port 4444
int main()
{
int sin_size;
struct sockaddr_in client_addr; 
sin_size=sizeof(struct sockaddr_in);
int hp = setupserversocket(port);
int h = accept(hp,(struct sockaddr *)(&client_addr),&sin_size);
}

