void printsocketaddr(const sockaddr *address, FILE *stream)
{if(address == NULL || stream == NULL)
return 0;
void *numadd;
char addbuffer[1000];
in_port_t port;
switch(address->sa_family){
case AF_INET:
numadd = &((struct sockaddr_in *)address)->sin_addr;
port = ntohs(((struct sockaddr_in *)address)->sin_port);
break;
case AF_INET6:
numadd = &((struct sockaddr_in6 *)address)->sin6_addr;
port = ntohs(((struct sockaddr_in6 *)address)->sin6_port);
break;
default:
fputs("unknown type", stream);
return 0;
}
if(inet_ntop(address->sa_family, numadd, addbuffer, sizeof(addbuffer)) == NULL)
fputs("invalid address", stream);
else{
fprintf(stream, "%s", addbuffer);
if(port != 0)
fprintf(stream, "-%u", port);
}
}



