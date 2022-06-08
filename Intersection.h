#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "Tile.h"
#include "TrafficLight.h"

class Intersection : public Tile {
    private:
        //Member variables
        Tile *north;
        Tile *south;
        Tile *east;
        Tile *west;
        TrafficLight *trafficLight;

    public:
        Intersection(TrafficLight* trafficLight); //Constructor
        ~Intersection(); //Destructor
        Intersection(const Intersection& other); //Copy constructor
        Intersection(Intersection&& other); //Move Constructor
        Intersection& operator=(Intersection&& other); //Move assignment operator
        Intersection& operator=(Intersection& other); //Copy assignment operator

        Tile *getNext() override; //Overrides tile's get next method to be more dependent on vehicle
        Tile *getPrev() override; //Overrides tile's get prev method to be more dependent on vehicle
        Tile *getRight(); //Returns right tile to allow a vehicle to turn right
        TrafficLight *getTrafficLight(); //Returns traffic light

        //Additional getter methods
        inline Tile *getNorth() { return north; };
        inline Tile *getEast() { return east; };
        inline Tile *getSouth() { return south; };
        inline Tile *getWest() { return west; };

        // Setter methods
        inline void setNorth(Tile *north) { this->north = north; }
        inline void setEast(Tile *east) { this->east = east; }
        inline void setSouth(Tile *south) { this->south = south; }
        inline void setWest(Tile *west) { this->west = west; }


};
#endif
