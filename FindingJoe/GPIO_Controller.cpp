//
// Created by root on 26/06/16.
//

#include <unistd.h>
#include <cstdio>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include "GPIO_Controller.h"

using namespace GPIO;


GPIO_Controller::GPIO_Controller(unsigned short pin, bool input, bool isPWM){
    gpionum = pin;
    directionflag = input;
    pwm = isPWM;
    fd = -1;
    readytouse = 0;
}

bool GPIO_Controller::exportgpio() {
    char gpio[5];
    int tempfd = -1;
    if(pwm)
    {
        tempfd = open(PWMPATH"/export",O_WRONLY);
        int len = sprintf(gpio,"%d",(gpionum));
        write(tempfd,gpio,len);
    }
    else
    {
        tempfd = open(GPIOPATH"/export",O_WRONLY);

        int len = sprintf(gpio,"%d",(gpionum));
        write(tempfd,gpio,len);
    }
    if(tempfd < 0) {
        perror("Export error");
        return false;
    }


    close(tempfd);
    ++readytouse;
    return true;
}


bool GPIO_Controller::unExportgpio() {
    char gpio[5];
    int tempfd = -1;
    memset(gpio,0,5);
    if(pwm)
        tempfd = open(PWMPATH"/unexport",O_WRONLY);
    else
        tempfd = open(GPIOPATH"/unexport",O_WRONLY);
    if(tempfd < 0) {
        perror("Unexport error");
        return false;
    }

    int len = sprintf(gpio,"%d",gpionum);
    write(tempfd,gpio,len);
    close(tempfd);
    return true;
}

bool GPIO_Controller::setDirection() {
    char fname[TEMPBUFLEN];
    int tempfd;
    memset(fname, 0,TEMPBUFLEN);
    if(pwm)
    {
        sprintf(fname,"%s/pwm%d/enable",PWMPATH,gpionum);
        tempfd = open(fname,O_WRONLY);
        if(tempfd < 0 ){
            perror("enable error");
            return false;
        }
        write(tempfd,"1",2);
        close(tempfd);
        memset(fname,0,strlen(fname));

        sprintf(fname,"%s/pwm%d/period",PWMPATH,gpionum);
        tempfd = open(fname,O_WRONLY);
        if(tempfd < 0 ){
            perror("period error");
            return false;
        }
        write(tempfd,PERIOD,8);
        close(tempfd);
        readytouse++;

        setValue(0);
    }
    else{
        sprintf(fname,"%s/gpio%d/direction",GPIOPATH,gpionum);
        tempfd = open(fname,O_WRONLY);
        if(tempfd < 0 ){
            perror("direction error");
            return false;
        }
        if(directionflag)
            write(tempfd,"out",4);
        else
            write(tempfd,"in",3);

        readytouse++;
        setValue(LOW);
        close(tempfd);
    }
    return true;
}

bool GPIO_Controller::setValue(int val) {
    char fname[50];
    char value[10];

    memset(fname,0,TEMPBUFLEN);
    memset(value,0,10);

    if(isReadyToUse()){
        if(pwm){
            sprintf(fname,"%s/pwm%d/duty_cycle",PWMPATH,gpionum);
            if(fd == -1)
                fd = open(fname,O_RDWR);
            if(fd < 0 ){
                perror("Duty_cycle error");
                return false;
            }
            // Period is 1000000
            sprintf(value,"%d",val*10000);
            write(fd,value,strlen(value));
        }
        else{
            sprintf(fname,"%s/gpio%d/value",GPIOPATH,gpionum);
            if(fd == -1)
                fd = open(fname,O_RDWR);
            if(fd < 0 ){
                perror("set value error");
                return false;
            }
            if(val)
                write(fd,"1",2);
            else
                write(fd,"0",2);
        }
    }
    else{
        return false;
    }
    return true;
}

int GPIO_Controller::getValue() {
    char fname[TEMPBUFLEN];
    char value[10];
    memset(fname,0,TEMPBUFLEN);
    memset(value,0,10);

    if(isReadyToUse()){
        if(pwm){
            sprintf(fname,"%s/pwm%d/duty_cycle",PWMPATH,gpionum);
            if(fd == -1)
                fd = open(fname,O_RDWR);
            if(fd < 0 ){
                perror("duty cycle read error");
                return false;
            }
            read(fd,value,10);
        }
        else{
            sprintf(fname,"%s/gpio%d/value",GPIOPATH,gpionum);
            if(fd == -1)
                fd = open(fname,O_RDWR);
            if(fd < 0 ){
                perror("set value error");
                return false;
            }
            read(fd,value,10);
        }
    }
    else{
        return -1;
    }
    return atoi(value);
}

GPIO_Controller::~GPIO_Controller() {
    unExportgpio();
}

bool GPIO_Controller::readyIt() {
    return exportgpio() && setDirection();
}
