#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
void userletime();
void sigiohandler(int signaltype);
int servsock;
int main(in argc, char *argv[])
{
if
