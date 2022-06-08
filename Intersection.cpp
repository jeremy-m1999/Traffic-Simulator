#ifndef __INTERSECTION_CPP__
#define __INTERSECTION_CPP__

#include "Tile.h"
#include "Intersection.h"
#include "TrafficLight.h"
#include "VehicleBase.h"
#include <iostream>

//Constructor
Intersection::Intersection(TrafficLight *trafficLight) : Tile()
{
  this->name = "Intersection";
  //Intersection tile needs a traffic light
  this->trafficLight = trafficLight;
}

Intersection::~Intersection(){}

//Copy constructor
Intersection::Intersection(const Intersection& other) {
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;
}

//Move constructor
Intersection::Intersection(Intersection&& other) {
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;

  other.north = nullptr;
  other.south = nullptr;
  other.east = nullptr;
  other.west = nullptr;
  other.trafficLight = nullptr;
}

//Move assignment operator
Intersection& Intersection::operator=(Intersection&& other) {
  if (this == &other) {
    return *this;
  }
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;

  //Canibalizes other
  other.north = nullptr;
  other.south = nullptr;
  other.east = nullptr;
  other.west = nullptr;
  other.trafficLight = nullptr;

  return *this;
}

//Copy assignment operator
Intersection& Intersection::operator=(Intersection& other){
  if (this == &other) {
    return *this;
  }
  north = other.north;
  south = other.south;
  east = other.east;
  west = other.west;
  trafficLight = other.trafficLight;

  return *this;
}

/*
Finds the next tile dependent on a vehicles direction
 */
Tile* Intersection::getNext() {
  if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::north) {
    return north;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::south) {
    return south;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::east) {
    return east;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::west) {
    return west;
  }
  else {
    return Tile::getNext();
  }
}

/*
Finds the previous tile dependent on a vehicles direction
 */
Tile* Intersection::getPrev() {
  if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::north) {
    return south;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::south) {
    return north;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::east) {
    return west;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::west) {
    return east;
  }
  else {
    return Tile::getPrev();
  }
}

/*
Finds the right tile dependent on a vehicles direction
 */
Tile* Intersection::getRight(){
  if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::north) {
    return east;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::south) {
    return west;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::east) {
    return south;
  }
  else if (getCurrentVehicle() -> getVehicleOriginalDirection() == Direction::west) {
    return north;
  }
  else {
    return Tile::getNext();
  }
}

//Returns a traffic light.
TrafficLight* Intersection::getTrafficLight() {
  return trafficLight;
}

#endif
