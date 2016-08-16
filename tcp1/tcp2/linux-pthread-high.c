int setnonblocking(int fd)
{
int old_option = fcntl(fd, F_GETFL);
int new_option = old_option | O_NONBLOCK;
fcntl(fd, F_SETFL, new_option);
return old_option;}

void addfd(int epollfd, int fd)
{
epoll_event event;
event.data,fd = fd;
event.events = EPOLLIN | EPOLLET;
epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
setnonblocking(fd);
}
void sig_handler(int sig){
int save_errno = errno;
int msg = sig;
send(pipefd[1], (char *)&msg, 1, 0);
errno = save_errno
}
void addsig(int sig)
{
struct sigaction sa;
memset(&sa, '\0', sizeof(sa));
sa.sa_handler = sig_handler;
sa_flags |= SA_RESTART;
sigfillset(&sa.sa_mask);
assert(sigaction(sig, &sa, NULL));xx
}

