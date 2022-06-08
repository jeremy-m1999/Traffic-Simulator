#ifndef __TILE_H__
#define __TILE_H__
#include <iostream>
using namespace std;

#include "VehicleBase.h"

class Tile {
  private :
    //Member variables
    bool emptyTile;
    VehicleBase *currentVehicle = nullptr;
    Tile *nextTile;
    Tile *prevTile;

  public :
    //Name of the tile to distringuish itself from intersection
    std::string name;
    Tile(); //Constructor
    ~Tile(); //Destructor
    Tile(const Tile& other); //Copy constructor
    Tile(Tile&& other); //Move constructor
    Tile& operator=(Tile&& other); //Move assignemnt operator
    Tile& operator=(Tile& other); //Copy assignment operator

    //Getters
    virtual Tile *getNext(); //Gets the next tile
    virtual Tile *getPrev(); //Gets the prev tile
    bool getTileStatus(); //Checks to see if a tile is open or occupied
    inline string getName() {return name;}
    VehicleBase* getCurrentVehicle(); //Finds vehicle occupying the tile

    void setOccupiedTile(VehicleBase* vehicle); //Sets the tile occupied to a vehicle
    void setOpenTile(); //Opens a tile

    void setNextTile(Tile* next); //Connects two tiles
    void setPrevTile(Tile* prev); //Connects two tiles
    inline bool containsVehicle() {return getCurrentVehicle() != nullptr;}; //Checks to see if a tile has a vehicle on them
    void setLeftTile(Tile* left); //Connects two tiles
    void setRightTile(Tile* right); //Connects two tiles

};
#endif
