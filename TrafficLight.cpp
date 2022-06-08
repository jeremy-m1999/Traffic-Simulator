#ifndef __TRAFFICLIGHT_CPP__
#define __TRAFFICLIGHT_CPP__

#include <iostream>
#include "TrafficLight.h"
#include "VehicleBase.h"

//Constructor
TrafficLight::TrafficLight(){}

//Constructor with parameters
TrafficLight::TrafficLight(LightColor lightColor, int timeGreen, int timeYellow, int timeRed)
    : lightColor(lightColor),
      timeGreen(timeGreen),
      timeRed(timeRed),
      timeYellow(timeYellow)
      //Potentially need the time change included as a parameter
    {
      if(lightColor == LightColor::green){
        timeChange = timeGreen;
      }
      if(lightColor == LightColor::yellow){
        timeChange = timeYellow;
      }
      if(lightColor == LightColor::red){
        timeChange = timeRed;
      }
    }

//Destructor
TrafficLight::~TrafficLight(){}

//Copy constructor
TrafficLight::TrafficLight(const TrafficLight &other)
  : lightColor(other.lightColor),
    timeGreen(other.timeGreen),
    timeRed(other.timeRed),
    timeYellow(other.timeYellow)

{}

//Move Constructor
TrafficLight::TrafficLight(TrafficLight &&other)
    : lightColor(other.lightColor),
      timeGreen(other.timeGreen),
      timeRed(other.timeRed),
      timeYellow(other.timeYellow){
        //Canibalizes other
        other.timeGreen = 0;
        other.timeYellow = 0;
        other.timeRed = 0;
}

//Copy Assignment Operator
TrafficLight& TrafficLight::operator=(const TrafficLight& other) {
  if (this == &other) {
    return *this;
  }
  lightColor = other.lightColor;
  timeGreen = other.timeGreen;
  timeRed = other.timeRed;
  timeYellow = other.timeYellow;
  return *this;
}

//Move Assignment Operator
TrafficLight& TrafficLight::operator=(TrafficLight&& other) {
  if (this == &other) {
    return *this;
  }
  lightColor = other.lightColor;
  timeGreen = other.timeGreen;
  timeRed = other.timeRed;
  timeYellow = other.timeYellow;
  //Canibalizes other
  other.timeGreen = 0;
  other.timeRed = 0;
  other.timeYellow = 0;
  return *this;
}

//Returns the current light color
LightColor TrafficLight::getLightColor() {
  return lightColor;
}

//Sets the light color of a traffic light based on the current light color and changes the time till light is changed
LightColor TrafficLight::setLightColor(LightColor col)
{
  if (col == LightColor::green)
  {
    timeChange = timeGreen;
  }
  else if (col == LightColor::yellow)
  {
    timeChange = timeYellow;
  }
  else
  {
    timeChange = timeRed;
  }

  LightColor old = lightColor;
  lightColor = col;
  return old;
}

//Returns the time the light stays green
int TrafficLight::getTimeGreen() {
  return timeGreen;
}

//Returns the time the light stays yellow
int TrafficLight::getTimeYellow() {
  return timeYellow;
}

//Returns the time the light stays red
int TrafficLight::getTimeRed() {
  return timeRed;
}

//Returns the time left before the light changes color
int TrafficLight::getTimeChange() {
  return timeChange;
}

//Decreases the time left before the light changes color by one second. Once the time left equals 0, the light color is changed
//Green becomes yellow, yellow becomes red, red becomes green
void TrafficLight::decreaseTime()
{
  //Reduces the time of the traffic light
  timeChange--;
  //Once the time change is 0, the lights are set to a different color and the time change is set to the time of that color light
  if (timeChange == 0)
  {
    //Green set to yellow
    if (lightColor == LightColor::green)
    {
      lightColor = LightColor::yellow;
      timeChange = timeYellow;
    }
    //Yellow set to red
    else if (lightColor == LightColor::yellow)
    {
      lightColor = LightColor::red;
      timeChange = timeRed;
    }
    //Red set to green
    else
    {
      lightColor = LightColor::green;
      timeChange = timeGreen;
    }
  }
}

#endif
