#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <time.h>
long t[5];
int fd;
void *f(void *a)
{
    int epfd=epoll_create1(0),i;
    struct epoll_event e,ev[1];
    char c;
    e.events=EPOLLPRI|EPOLLERR;
    e.data.fd=fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&e);
    for (i=0; 
        i < 5; 
        i++) {epoll_wait(epfd,ev,1,-1);
        lseek(fd,0,SEEK_SET);
        read(fd,&c,1);
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC,&ts);
        t[i]=ts.tv_sec;
    }
    close(epfd);
    return NULL;
}
int main()
{
    pthread_t th;
    int x;
    char c;
    x=open("/sys/class/gpio/export",O_WRONLY);
    write(x,"69",2);
    close(x);
    x=open("/sys/class/gpio/gpio69/direction",O_WRONLY);
    write(x,"in",2);
    close(x);
    x=open("/sys/class/gpio/gpio69/edge",O_WRONLY);
    write(x,"rising",6);
    close(x);
    fd=open("/sys/class/gpio/gpio69/value",O_RDONLY|O_NONBLOCK);
    lseek(fd,0,SEEK_SET);
    read(fd,&c,1);
    pthread_create(&th,NULL,f,NULL);
    pthread_join(th,NULL);
    for (x=0;
        x<5;
        x++) printf("%ld\n",t[x]);
    close(fd);
    x=open("/sys/class/gpio/unexport",O_WRONLY);
    write(x,"69",2);
    close(x);
    return 0;
}