#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__



// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};

class VehicleBase
{
   public:
      static int vehicleCount;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
      int length;
      bool turnRight;

   public:
      VehicleBase();
      VehicleBase(VehicleType type, Direction originalDirection, bool turnRight);
      VehicleBase(VehicleType type, Direction originalDirection);
      VehicleBase(const VehicleBase& other);
      VehicleBase(VehicleBase&& other);
      VehicleBase& operator=(VehicleBase&& other);
      VehicleBase& operator=(VehicleBase& other);
      ~VehicleBase();

      inline int getVehicleID() const { return this->vehicleID; };
      inline VehicleType getVehicleType() const { return this->vehicleType; };
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; };
      inline void   setVehicleNewDirection(Direction direction) {this -> vehicleDirection = direction;};
      inline int getLength() const{return this -> length;};
      inline bool willTurnRight() const{return this -> length;};
      inline void setDirectionRight() {this -> turnRight = true;};
      inline void setDirectionNotRight() {this -> turnRight = false;};
};

#endif
