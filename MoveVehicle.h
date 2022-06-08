#ifndef __MOVEVEHICLE_H__
#define __MOVEVEHICLE_H__

#include "VehicleBase.h"
#include "Tile.h"
#include "Intersection.h"

class MoveVehicle : public VehicleBase
{

  enum Turn
  {
    LEFT,
    RIGHT,
    STRAIGHT
  };

private:
  //Member variables
  int length;
  Tile *hptr;
  Tile *tptr;
  bool willTurnRight;
  bool isTurningRight = false;
  int movesLeftInTurn;
  Direction currDirection;
  bool hasGreen = false;
  bool reachedEndOfRoad = false;

  void setOccupiedTiles(); // Set all Tiles between head and tail to occupied
  void moveForward();      // Move the car forward a Tile

public:
  //Constructor
  MoveVehicle(VehicleType vehicleType, Direction direction, int vehicleLength, bool willTurnRight);

  // Destructor
  ~MoveVehicle();

  // Getter methods
  int getLength();
  Direction getCurrDirection();
  Tile *getHptr();
  Tile *getTptr();
  Turn getTurn();
  inline bool hasReachedEndOfRoad() { return this->reachedEndOfRoad; }

  // Setter methods
  void setCurrDirection(Direction direction);

  void move();                //Moves a vehicle base forward
  void turnRight();           //Moves a vehicle right
  void enterRoad(Tile *tptr); //Sets a vehicle onto a road
};

#endif
