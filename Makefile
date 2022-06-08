EXECS = simulation
OBJS = simulation.o Animator.o VehicleBase.o Tile.o TrafficLight.o Road.o Intersection.o MoveVehicle.o

CC = g++
CCFLAGS = -std=c++17

all: $(EXECS)

simulation: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)
