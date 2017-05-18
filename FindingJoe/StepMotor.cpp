//
// Created by emre on 5/1/17.
//

#include <cstdio>
#include <zconf.h>
#include "StepMotor.h"

StepMotor::StepMotor(int enable, int step, int dir) : enablePin(enable,true,false),
                                                      direction(dir,true,false),
                                                      stepPin(step, true,false)
{
    if( enablePin.readyIt() && direction.readyIt() && stepPin.readyIt())
    {
        ready = true;
        enablePin.setValue(1);
        direction.setValue(0);
        stepPin.setValue(0);
    }
    else
        ready = false;
}

void StepMotor::GoStep(int step = 1,bool isOpposite = false) {
    if(isReady()){
        enablePin.setValue(0);
        usleep(500);
        if(isOpposite)
            direction.setValue(1);
	else
	    direction.setValue(0);
        for (int i = 0; i <  step; ++i) {
            stepPin.setValue(1);
            usleep(1000);
            stepPin.setValue(0);
            usleep(1000);
	}
        stepPin.setValue(0);
	usleep(800);
	enablePin.setValue(1);
    }
    else{
        perror("pins are not Ready");
    }
}
