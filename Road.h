#ifndef __ROAD_H__
#define __ROAD_H__

#include "VehicleBase.h"
#include "TrafficLight.h"
#include "Tile.h"
#include "Intersection.h"
#include <vector>

class Road {
    private:
        //Member variables
        vector<Tile *> road;
        int roadLength;
        Direction direction;
        //Boolean of front and back of vehicles at tile i.
        inline bool isFrontofVehicle(int tileIndex){return (road.at(tileIndex)->getCurrentVehicle()->getVehicleID() != road.at(tileIndex)->getNext()->getCurrentVehicle()->getVehicleID());};
        inline bool isBackofVehicle(int tileIndex){return (road.at(tileIndex)->getCurrentVehicle()->getVehicleID() != road.at(tileIndex)->getPrev()->getCurrentVehicle()->getVehicleID());};


    public:
        Road(); //Constructor
        Road(int number_of_sections_before_intersection, Intersection* it1, Intersection* it2, Direction direction); //Constructor
        ~Road(); //Destructor
        Road(const Road& other); //Copy Constructor
        Road(Road&& other); //Move Constructor
        Road& operator=(Road&& other); //Move assignment operator
        Road& operator=(Road& other); //Copy assignment operator

        Tile* getTile(int index); //Finds tile at index i
        //Getters
        int getLength();
        Direction getDirection();

        //Boolean values
        bool canDeleteVehicle();
        bool canCreateVehicle(VehicleBase* vehicle);
        
        void CreateVehicle(VehicleBase* vehicle);
        void DeleteVehicle(VehicleBase* vehicle);
        void moveVehicleForward(int tileIndex);
        void moveVehicleRight(int tileIndex, Tile* right);
        Tile* findBackofCar(int index);
        void moveVehicles(int number_of_sections_before_intersection, Intersection* turnTile, TrafficLight light);
        vector<VehicleBase *> currVehicles();
        void setOccupiedTiles(VehicleBase vehicle);

};

#endif
