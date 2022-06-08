#ifndef __MOVEVEHICLE_CPP__
#define __MOVEVEHICLE_CPP__

#include "MoveVehicle.h"
#include "VehicleBase.h"
#include <iostream>
#include "Intersection.h"
using namespace std;

//Constructor
MoveVehicle::MoveVehicle(VehicleType vehicleType, Direction direction, int vehicleLength, bool willTurnRight) : VehicleBase(vehicleType, direction)
{
   this->length = vehicleLength;
   this->willTurnRight = willTurnRight; // Whether Vehicle will turn right or now
}

//Destructor
MoveVehicle::~MoveVehicle()
{
}



//Returns length of a vehicle
int MoveVehicle::getLength()
{
   return length;
}

//Returns current direction of a vehicle
Direction MoveVehicle::getCurrDirection()
{
   return this->currDirection;
}

//Sets all tiles of a vehicle occupying them to occupied
void MoveVehicle::setOccupiedTiles()
{
   // Set the Tile where head is to occupied
   this->hptr->setOccupiedTile(this);

   //Sets all tiles between head and tail to occupied
   Tile *currTile = this->tptr;
   while (currTile != this->hptr)
   {
      // Set the tile to occupied
      currTile->setOccupiedTile(this);

      // Check the current tile is an IntersectionTile to account for turns
      if (this->isTurningRight && currTile->getName() == "Intersection"){
         currTile = dynamic_cast<Intersection *>(currTile)->getRight();
      }
      else
      {
         currTile = currTile->getNext();
      }
   }
}

//Allows a vehicle to enter the road.
void MoveVehicle::enterRoad(Tile *hptr)
{
   this->hptr = hptr; // Set head pointer
   this->tptr = hptr; // Tail is initially same as head

   // Move the tail backward the length of the car to "drive" on to the Road
   for (int i = 0; i < this->length - 1; i++)
   {
     //Locates the back of a vehicle
      this->tptr = this->tptr->getPrev();
   }

   // Set all the Tiles between head and tail to occupied
   this->setOccupiedTiles();
}

//Moves a vehicle forward
void MoveVehicle::moveForward()
{
   // Set the previous tile to unoccupied
   Tile *prevt = this->tptr;

   //Moves the front and back of a vehicle
   this->hptr = this->hptr->getNext();
   this->tptr = this->tptr->getNext();

   //Sets former tile of a vehicle's rear to open since it moves
   prevt->setOpenTile();

   // Set the tiles between head and tail to occupied
   this->setOccupiedTiles();
}

//Moves a vehicle forward or right
void MoveVehicle::move()
{

   // If vehicle is turning right, it needs to turn right
   if (this->isTurningRight)
   {
      turnRight();
      return;
   }

   // Get the next Tile
   Tile *next = this->hptr->getNext();

   // Check if next Tile 1) exists and 2) is unoccupied
   if (next != nullptr && !next->containsVehicle())
   {

      // The next tile is an IntersectionTile and we don't already have a green light
      if (next->getName() == "Intersection" && !this->hasGreen)
      {
         //Tile is now IntersectionTile
         Intersection *it = dynamic_cast<Intersection *>(next);

         //Finds the corresponding traffic light color which affects how the vehicle moves
         LightColor lightColor = it->getTrafficLight()->getLightColor();

         // If the light is yellow, only vehicles inside the intersection can move.
         if (lightColor == LightColor::yellow)
         {
            if (it->getTrafficLight()->getTimeChange() >= this->length + 1 && this->willTurnRight)
            {
               turnRight();
               return;
            }

            if (it->getTrafficLight()->getTimeChange() >= this->length + 2)
            {
               this->hasGreen = true;
               this->moveForward();
            }
         }
         //If the light color is green, vehicles before the traffic intersection can still move
         else if (lightColor == LightColor::green)
         {
            this->hasGreen = true;

            //If a vehicle is turning right, it will turn right.
            if (this->willTurnRight)
            {
               turnRight();
               return;
            }

            this->moveForward();
         }
      }
      else
      {
         // Move forward to the next Tile
         this->moveForward();
      }
   }
   else if (next == NULL)
   {
      //Checks to see if a tile has reached the end of a road
      this->reachedEndOfRoad = true;

      Tile *tail = this->tptr;
      //Opens the tiles from the back of a vehicle
      while (tail != hptr)
      {
        //Opens the tile up so another vehicle can occupy it.
         tail->setOpenTile();
         //Gets the next tile.
         tail = tail->getNext();
      }
      //Sets the open tile.
      this->hptr->setOpenTile();
   }
}

//Used in move to handle a vehicle turning right
void MoveVehicle::turnRight()
{

   // Set turning right to true if it isn't already
   if (!this->isTurningRight)
   {
      this->isTurningRight = true;
      this->movesLeftInTurn = this->length + 1;
   }

   if (this->movesLeftInTurn != 0)
   {
      // Set prev tiles
      Tile *prevt = this->tptr;
      Tile *prevh = this->hptr;

      //Starts moving right when a vehicles head is at an intersection
      if (this->hptr->getName() == "Intersection")
      {
         // Downcast to IntersectionTile
         Intersection *headIntersection = dynamic_cast<Intersection *>(this->hptr);

         //Gets the right tile next to an intersection
         this->hptr = headIntersection->getRight();

         //Moves the vehicle right by affecting the tail pointer
         this->tptr->setOpenTile();
         this->tptr = this->tptr->getNext();
/*
         // Set the spot where the head was to unoccupied
         prevh->setOpenTile();
*/
      }
      // Check if the tail is on an IntersectionTile
      else if (this->tptr->getName() == "Intersection")
      {
         // Downcast to IntersectionTile
         Intersection *tailIntersectionTile = dynamic_cast<Intersection *>(this->tptr);

         // Set the tail to the right of the IntersectionTile
         this->tptr = tailIntersectionTile->getRight();

         //Moves the head of the vehicle
         this->hptr->setOpenTile();
         this->hptr = this->hptr->getNext();

         // Set the spot where the tail was to unoccupied (unescessary but for consistency)
         prevt->setOpenTile();
      }
      else
      {
         // If the head and tail are not on IntersectionTiles, move head and tail forward
         moveForward();
      }
      //Sets tiles between the front and back of the vehicle to occupied
      this->setOccupiedTiles();
      movesLeftInTurn--;
   }

   //Once the vehicle turns fully right, the boolean isTurningRight should be false.
   if (movesLeftInTurn == 0)
   {
      this->isTurningRight = false;
   }
}

//Changes the direction a vehicle, typically used when a vehicle is turning right
void MoveVehicle::setCurrDirection(Direction direction)
{
   this->currDirection = direction;
}


#endif
