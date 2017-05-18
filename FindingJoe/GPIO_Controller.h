//
// Created by root on 26/06/16.
//

#ifndef GALILEO_GPIO_CONTROLLER_H
#define GALILEO_GPIO_CONTROLLER_H

#ifndef HIGH
    #define HIGH 1
#endif

#ifndef LOW
    #define LOW 0
#endif

#define TEMPBUFLEN 50
#define PERIOD "1000000"

namespace GPIO {
    // CONSTANT VARIABLES
    const short ENDGPIONUMBER = 55;
    const short STARTGPIONUMBER = 0;
    // pwm channels 3,5,6,9,10,11

    /**
     * Requirements paths
     */
    #define GPIOPATH "/sys/class/gpio"
    #define PWMPATH "/sys/class/pwm/pwmchip0"

    /**
     * GPIO Controller Class
     *
     * call first exportgpio, then set direction, then use it with set value method.
     */
    class GPIO_Controller {
    public:
        GPIO_Controller(unsigned short pin,bool output,bool isPWM);

        /**
         * Enables the Gpio
         */
        bool exportgpio();
        /**
         * Disables the gpio
         */
        bool unExportgpio();
        /**
         * Sets direction,input or output.
         */
        bool setDirection();
        /**
         * Sets Value Pwm mode is percentage 0 to 100
         * normal usage is 0 or positive any number.
         */
        bool setValue(int val);
        /**
         * Gets Value from pin
         */
        int getValue();
        /**
         * Makes every thing automaticcaly after this method you can use directly setValue method.
         */
        bool readyIt();
        /**
         * Checks is ReadyToUse This pin.
         */
        inline bool isReadyToUse(){
            return readytouse == 2;
        }

        virtual ~GPIO_Controller();
    private:
        bool pwm;
        short gpionum;
        bool directionflag;
        int fd;
        short readytouse;
    };
}

#endif //GALILEO_GPIO_CONTROLLER_H
