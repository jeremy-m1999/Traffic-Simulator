#ifndef __SIMULATION_CPP__
#define __SIMULATION_CPP__

#include <fstream>
#include <iostream>
#include <random>
#include <iterator>
#include <vector>

#include "Animator.h"
#include "string"
#include "VehicleBase.h"
#include "TrafficLight.h"
#include "Intersection.h"
#include "Road.h"
#include "Tile.h"
#include "MoveVehicle.h"

using namespace std;

int main(int argc, char* argv[]){
    int seed = argc;
    int maximum_simulated_time;
    int number_of_sections_before_intersection;
    int green_north_south;
    int yellow_north_south;
    int green_east_west;
    int yellow_east_west;
    double prob_new_vehicle_northbound;
    double prob_new_vehicle_eastbound;
    double prob_new_vehicle_westbound;
    double prob_new_vehicle_southbound;
    double proportion_of_cars;
    double proportion_of_SUVs;
    double proportion_right_turn_cars;
    double proportion_right_turn_SUVs;
    double proportion_left_turn_cars;
    double proportion_left_turn_SUVs;
    double proportion_right_turn_trucks;
    double proportion_left_turn_trucks;


    ifstream infile;
    infile.open(argv[1]);

    std::string temp;
    double i = 0.0;

    while(infile.good()){
        infile >> temp;
        infile >> i;

        if(temp == "maximum_simulated_time:"){
            maximum_simulated_time = static_cast<int>(i);
        }
        if(temp == "number_of_sections_before_intersection:"){
            number_of_sections_before_intersection = static_cast<int>(i);
        }
        if(temp == "green_north_south:"){
            green_north_south = static_cast<int>(i);
        }
        if (temp == "yellow_north_south:"){
            yellow_north_south = static_cast<int>(i);
        }
        if (temp == "green_east_west:"){
            green_east_west = static_cast<int>(i);
        }
        if (temp == "yellow_east_west:"){
            yellow_east_west = i;
        }
        if (temp == "prob_new_vehicle_northbound:"){
            prob_new_vehicle_northbound = i;
        }
        if (temp == "prob_new_vehicle_southbound:"){
            prob_new_vehicle_southbound = i;
        }
        if (temp == "prob_new_vehicle_eastbound:"){
            prob_new_vehicle_eastbound = i;
        }
        if (temp == "prob_new_vehicle_westbound:"){
            prob_new_vehicle_westbound = i;
        }
        if (temp == "proportion_of_cars:"){
            proportion_of_cars = i;
        }
        if (temp == "proportion_of_SUVs:"){
            proportion_of_SUVs = i;
        }
        if (temp == "proportion_right_turn_cars:"){
            proportion_right_turn_cars = i;
        }
        if (temp == "proportion_left_turn_cars:"){
            proportion_left_turn_cars = i;
        }
        if (temp == "proportion_right_turn_SUVs:"){
            proportion_right_turn_SUVs = i;
        }
        if (temp == "proportion_left_turn_SUVs:"){
            proportion_left_turn_SUVs = i;
        }
        if (temp == "proportion_right_turn_trucks:"){
            proportion_right_turn_trucks = i;
        }
        if (temp == "proportion_left_turn_trucks:"){
            proportion_left_turn_trucks = i;
        }
    }
    infile.close();

    vector<MoveVehicle *> vehicles;

    // Create Animator
    Animator animator(number_of_sections_before_intersection);


    TrafficLight lightNS(LightColor::green, green_north_south, yellow_north_south, green_east_west + yellow_east_west);
    TrafficLight lightEW(LightColor::red, green_east_west, yellow_east_west, green_north_south + yellow_north_south);


    Intersection NorthwestTile(&lightNS);
    Intersection NortheastTile(&lightEW);
    Intersection SouthwestTile(&lightEW);
    Intersection SoutheastTile(&lightNS);

    Road northbound(number_of_sections_before_intersection, &SoutheastTile, &NortheastTile, Direction::north);
    Road southbound(number_of_sections_before_intersection, &NorthwestTile, &SouthwestTile, Direction::south);
    Road eastbound(number_of_sections_before_intersection, &SouthwestTile, &SoutheastTile, Direction::east);
    Road westbound(number_of_sections_before_intersection, &NortheastTile, &NorthwestTile, Direction::west);



    mt19937 random_number_generator(seed);
    int time = 0;
    uniform_real_distribution<double> rand_double(0, 1.0);
    double probability_direction;
    double probability_turning;
    double probability_vehicle;


    while(time <= maximum_simulated_time){
        //South
        probability_direction = rand_double(random_number_generator);
        probability_vehicle = rand_double(random_number_generator);
        probability_turning = rand_double(random_number_generator);
        Direction direction = Direction::south;
        if(probability_direction <= prob_new_vehicle_southbound){
            if(probability_vehicle <= proportion_of_cars){
                if(probability_turning <= proportion_right_turn_cars){
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, true);
                    a->enterRoad(southbound.getTile(4));
                    vehicles.push_back(a);
                }
                else{
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, false);
                    a->enterRoad(southbound.getTile(4));
                    vehicles.push_back(a);
                }

            }

            else if((probability_vehicle > proportion_of_cars) && (probability_vehicle <= proportion_of_cars + proportion_of_SUVs)){
                if(probability_turning <= proportion_right_turn_SUVs){
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, true);
                    b->enterRoad(southbound.getTile(4));
                    vehicles.push_back(b);
                }
                else{
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, false);
                    b->enterRoad(southbound.getTile(4));
                    vehicles.push_back(b);
                }
            }
            else{
                if(probability_turning <= proportion_right_turn_trucks){
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, true);
                    c->enterRoad(southbound.getTile(4));
                    vehicles.push_back(c);
                }
                else{
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, false);
                    c->enterRoad(southbound.getTile(4));
                    vehicles.push_back(c);
                }
            }
        }

        //North
        probability_direction = rand_double(random_number_generator);
        probability_vehicle = rand_double(random_number_generator);
        probability_turning = rand_double(random_number_generator);
        direction = Direction::north;
        if(probability_direction <= prob_new_vehicle_northbound){
            if(probability_vehicle <= proportion_of_cars){
                if(probability_turning <= proportion_right_turn_cars){
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, true);
                    a->enterRoad(northbound.getTile(4));
                    vehicles.push_back(a);
                }
                else{
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, false);
                    a->enterRoad(northbound.getTile(4));
                    vehicles.push_back(a);
                }
            }
            else if((probability_vehicle > proportion_of_cars) && (probability_vehicle <= proportion_of_cars + proportion_of_SUVs)){
                if(probability_turning <= proportion_right_turn_SUVs){
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, true);
                    b->enterRoad(northbound.getTile(4));
                    vehicles.push_back(b);
                }
                else{
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, false);
                    b->enterRoad(northbound.getTile(4));
                    vehicles.push_back(b);
                }
            }
            else{
                if(probability_turning <= proportion_right_turn_trucks){
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, true);
                    c->enterRoad(northbound.getTile(4));
                    vehicles.push_back(c);
                }
                else{
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, false);
                    c->enterRoad(northbound.getTile(4));
                    vehicles.push_back(c);
                }
            }
        }
        //East
        probability_direction = rand_double(random_number_generator);
        probability_vehicle = rand_double(random_number_generator);
        probability_turning = rand_double(random_number_generator);
        direction = Direction::east;
        if(probability_direction <= prob_new_vehicle_eastbound){
            if(probability_vehicle <= proportion_of_cars){
                if(probability_turning <= proportion_right_turn_cars){
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, true);
                    a->enterRoad(eastbound.getTile(4));
                    vehicles.push_back(a);
                }
                else{
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, false);
                    a->enterRoad(eastbound.getTile(4));
                    vehicles.push_back(a);
                }

            }
            else if((probability_vehicle > proportion_of_cars) && (probability_vehicle <= proportion_of_cars + proportion_of_SUVs)){
                if(probability_turning <= proportion_right_turn_SUVs){
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, true);
                    b->enterRoad(eastbound.getTile(4));
                    vehicles.push_back(b);
                }
                else{
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, false);
                    b->enterRoad(eastbound.getTile(4));
                    vehicles.push_back(b);
                }
            }
            else{
                if(probability_turning <= proportion_right_turn_trucks){
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, true);
                    c->enterRoad(eastbound.getTile(4));
                    vehicles.push_back(c);
                }
                else{
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, false);
                    c->enterRoad(eastbound.getTile(4));
                    vehicles.push_back(c);
                }
            }
        }

        //West
        probability_direction = rand_double(random_number_generator);
        probability_vehicle = rand_double(random_number_generator);
        probability_turning = rand_double(random_number_generator);
        direction = Direction::west;
        if(probability_direction <= prob_new_vehicle_westbound){
            if(probability_vehicle <= proportion_of_cars){
                if(probability_turning <= proportion_right_turn_cars){
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, true);
                    a->enterRoad(westbound.getTile(4));
                    vehicles.push_back(a);

                }
                else{
                    MoveVehicle *a = new MoveVehicle(VehicleType::car, direction, 2, false);
                    a->enterRoad(westbound.getTile(4));
                    vehicles.push_back(a);
                }

            }
            else if((probability_vehicle > proportion_of_cars) && (probability_vehicle <= proportion_of_cars + proportion_of_SUVs)){
                if(probability_turning <= proportion_right_turn_SUVs){
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, true);
                    b->enterRoad(westbound.getTile(4));
                    vehicles.push_back(b);

                }
                else{
                    MoveVehicle *b = new MoveVehicle(VehicleType::suv, direction, 3, false);
                    b->enterRoad(westbound.getTile(4));
                    vehicles.push_back(b);

                }
            }
            else{
                if(probability_turning <= proportion_right_turn_trucks){
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, true);
                    c->enterRoad(westbound.getTile(4));
                    vehicles.push_back(c);
                }
                else{
                    MoveVehicle *c = new MoveVehicle(VehicleType::truck, direction, 4, false);
                    c->enterRoad(westbound.getTile(4));
                    vehicles.push_back(c);
                }

            }
        }



    for(int i = 0; i < vehicles.size(); i++){
        vehicles[i] -> move();
    }

        animator.setVehiclesEastbound(eastbound.currVehicles());
        animator.setVehiclesNorthbound(northbound.currVehicles());
        animator.setVehiclesSouthbound(southbound.currVehicles());
        animator.setVehiclesWestbound(westbound.currVehicles());

        animator.setLightEastWest(lightEW.getLightColor());
        animator.setLightNorthSouth(lightNS.getLightColor());

        animator.draw(time);

        cin.ignore();

        lightNS.decreaseTime();
        lightEW.decreaseTime();

        time++;
        if(time == maximum_simulated_time){
            for(int i = 0; i < vehicles.size(); i++){
                delete vehicles[i];
            }
            vehicles.clear();
        }
    }
    return 0;

}

#endif
