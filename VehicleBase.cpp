#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

//Constuctor
VehicleBase::VehicleBase(){}

//Constuctor
VehicleBase::VehicleBase(VehicleType type, Direction direction, bool turnRight)
    : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction),
      turnRight(turnRight)
{
  //Sets corresponding lengths for each type of car
  if(type == VehicleType::car){
        this -> length = 2;
    }
    else if(type == VehicleType::suv){
        this -> length = 3;
    }
    else{
        this -> length = 4;
    }
}

//Constructor
VehicleBase::VehicleBase(VehicleType type, Direction direction)
  : vehicleID(VehicleBase::vehicleCount++),
      vehicleType(type),
      vehicleDirection(direction)
{
  if(type == VehicleType::car){
        this -> length = 2;
    }
    else if(type == VehicleType::suv){
        this -> length = 3;
    }
    else{
        this -> length = 4;
    }
}

//Copy Constructor
VehicleBase::VehicleBase(const VehicleBase &other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      turnRight(other.turnRight)
{
  if(other.vehicleType == VehicleType::car){
        this -> length = 2;
    }
    else if(other.vehicleType == VehicleType::suv){
        this -> length = 3;
    }
    else{
        this -> length = 4;
    }
}

//Move Constructor
VehicleBase::VehicleBase(VehicleBase&& other)
    : vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      turnRight(other.turnRight)
{
  if(other.vehicleType == VehicleType::car){
        this -> length = 2;
    }
    else if(other.vehicleType == VehicleType::suv){
        this -> length = 3;
    }
    else{
        this -> length = 4;
    }
    other.vehicleID = 0;
    other.turnRight = true;
}

//Copy Assignment Operator
VehicleBase& VehicleBase::operator=(VehicleBase& other) {
  if (this == &other) {
    return *this;
  }
  vehicleID = other.vehicleID;
  vehicleType = other.vehicleType;
  vehicleDirection = other.vehicleDirection;
  turnRight = other.turnRight;

  return *this;
}

//Move Assignment Operator
VehicleBase& VehicleBase::operator=(VehicleBase&& other) {
  if (this == &other) {
    return *this;
  }
  vehicleID = other.vehicleID;
  length = other.length;
  vehicleType = other.vehicleType;
  vehicleDirection = other.vehicleDirection;
  turnRight = other.turnRight;

  other.vehicleID = 0;
  other.length = 0;
  other.turnRight = true;
  return *this;
}

//Destructor
VehicleBase::~VehicleBase() {}


#endif
