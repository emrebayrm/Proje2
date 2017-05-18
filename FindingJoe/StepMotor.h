//
// Created by emre on 5/1/17.
//

#ifndef GALILEO_STEPMOTOR_H
#define GALILEO_STEPMOTOR_H

#include "GPIO_Controller.h"

class StepMotor {
public:
    StepMotor(int enable,int step,int dir);

    void GoStep(int step, bool isOpposite);

    bool isReady(){
        return ready;
    }
private:
    bool ready;
    GPIO::GPIO_Controller enablePin;
    GPIO::GPIO_Controller stepPin;
    GPIO::GPIO_Controller direction;

};


#endif //GALILEO_STEPMOTOR_H
