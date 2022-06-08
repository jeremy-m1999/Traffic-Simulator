#ifndef __TRAFFICLIGHT_H__
#define __TRAFFICLIGHT_H__

#include "VehicleBase.h"

class TrafficLight {
    private:
        //Member Variables
        LightColor lightColor;
        int timeGreen;
        int timeRed;
        int timeYellow;
        int timeChange;
    public:
        TrafficLight(); //Constructor
        TrafficLight(LightColor lightColor, int timeGreen, int timeRed, int timeYellow); //Constructor
        TrafficLight(const TrafficLight &other); //Copy Constructor
        TrafficLight(TrafficLight &&other); //Move Constructor
        TrafficLight& operator=(const TrafficLight& other); //Copy assignment operator
        TrafficLight& operator=(TrafficLight&& other); //Move assignment operator
        ~TrafficLight(); //Destructor

        //Setters
        LightColor getLightColor();
        LightColor setLightColor(LightColor lightColor);

        //Getters
        int getTimeGreen();
        int getTimeRed();
        int getTimeYellow();
        int getTimeChange();

        void decreaseTime();
};
#endif
