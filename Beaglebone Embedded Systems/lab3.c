#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define b1 67
#define b2 69
#define PWM "/dev/bone/pwm/1/b"
void w(char *pa,char *v){int f=open(pa,O_WRONLY);
    write(f,v,strlen(v));
    close(f);
}int p(int f){char c='1';
    lseek(f,0,SEEK_SET);
    read(f,&c,1);
    return c=='0';
}void pl(int h,int du){char bu[20];
    int pe=1000000000/h;
    int dc=pe*du/100;
    w(PWM "/enable","0");
    sprintf(bu,"%d",pe);
    w(PWM "/period",bu);
    sprintf(bu,"%d",dc);
    w(PWM "/duty_cycle",bu);
    w(PWM "/enable","1");
    sleep(5);
    w(PWM "/enable","0");
}int main(){int f1,f2;
    char p1[40],p2[40];
    system("config-pin P8_08 gpio");
    system("config-pin P8_09 gpio");
    system("config-pin P9_16 pwm");
    w("/sys/class/gpio/export","67");
    w("/sys/class/gpio/export","69");
    w("/sys/class/gpio/gpio67/direction","in");
    w("/sys/class/gpio/gpio69/direction", "in");
    sprintf(p1,"/sys/class/gpio/gpio%d/value",b1);
    sprintf(p2,"/sys/class/gpio/gpio%d/value",b2);
    f1=open(p1,O_RDONLY);
    f2=open(p2,O_RDONLY);
    while (1){if (p(f1)){pl(100,60);
            while (p(f1));
        }if (p(f2)){pl(1000,70);
            while (p(f2));
        }usleep(50000);
    }return 0;
}