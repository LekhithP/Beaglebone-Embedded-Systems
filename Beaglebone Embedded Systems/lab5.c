#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <sys/epoll.h>
#define A 69
#define B 10
#define C 50
struct data_type{struct timespec timestamp;
    pthread_t thread_id;
};
struct data_type buffer[B];
pthread_mutex_t D=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t E=PTHREAD_COND_INITIALIZER,F=PTHREAD_COND_INITIALIZER;
int G=0,H=0,I=0;
void J(const char *M,const char *s){int f=open(M,O_WRONLY);
    if(f>=0){write(f,s,strlen(s));
        close(f);
    }}void K(void){char M[64],N[8];
    sprintf(M,"/sys/class/gpio/gpio%d",A);
    if(access(M,F_OK)){sprintf(N,"%d",A);
        J("/sys/class/gpio/export",N);
        usleep(100000);
    }sprintf(M,"/sys/class/gpio/gpio%d/direction",A);
    J(M,"in");
    sprintf(M,"/sys/class/gpio/gpio%d/edge",A);
    J(M,"rising");
}void *inputThread(void *L){char M[64],O[8];
    struct epoll_event P,Q;
    int R,S,T=0;
    K();
    sprintf(M,"/sys/class/gpio/gpio%d/value",A);
    R=open(M,O_RDONLY|O_NONBLOCK);
    S=epoll_create1(0);
    P.events=EPOLLPRI|EPOLLERR;
    P.data.fd=R;
    epoll_ctl(S,EPOLL_CTL_ADD,R,&P);
    read(R,O,8);
    while(T<C){if(epoll_wait(S,&Q,1,-1)<0){if(errno==EINTR)continue;
        break;
    }lseek(R,0,SEEK_SET);
    read(R,O,8);
        pthread_mutex_lock(&D);
        while(I==B)pthread_cond_wait(&F,&D);
        clock_gettime(CLOCK_MONOTONIC,&buffer[G].timestamp);
        buffer[G].thread_id=pthread_self();
        G=(G+1)%B;
        I++;
        T++;
        pthread_cond_signal(&E);
        pthread_mutex_unlock(&D);
    }close(S);
    close(R);
    return NULL;
}void *outputThread(void *L){FILE *f=fopen("lekhith_ponnaluru_data.txt","w");
    int T=0;
    struct data_type U;
    while(T<C){pthread_mutex_lock(&D);
        while(I==0)pthread_cond_wait(&E,&D);
        U=buffer[H];
        H=(H+1)%B;
        I--;
        T++;
        pthread_cond_signal(&F);
        pthread_mutex_unlock(&D);
        fprintf(f,"%ld %ld %lu\n",U.timestamp.tv_sec,U.timestamp.tv_nsec,(unsigned long)U.thread_id);
        printf("%ld %ld %lu\n",U.timestamp.tv_sec,U.timestamp.tv_nsec,(unsigned long)U.thread_id);
    }fclose(f);
    return NULL;
}int main(void){pthread_t V,W;
    pthread_create(&W,0,outputThread,0);
    pthread_create(&V,0,inputThread,0);
    pthread_join(V,0);
    pthread_join(W,0);
    return 0;
}