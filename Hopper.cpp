//
// Created by brind on 15/04/2024.
//

#include "Hopper.h"
#include <iostream>

using namespace std;

Hopper::Hopper(int id, pair<int, int> position, direction dir, int size, int hopLength) : Bug(id, position, dir, size){
    this->hopLength = hopLength;
}

void Hopper::move() {

    if(isWayBlocked() == true) {
        changeDirection();
        move();
    }
    else {
        switch(dir) {
            case NORTH:
                position.first = max(0,position.first-hopLength);
                break;
            case SOUTH:
                position.first = min(9,position.first+hopLength);
                break;
            case WEST:
                position.second = max(0,position.second-hopLength);
                break;
            case EAST:
                position.second = min(9,position.second+hopLength);
                break;
        }
        updatePath();
    }

}

void Hopper::displayBug() {
    printf("%-4d %-8s %-10s %-5d %-10s %-5d %9s\n",id,"Hopper",get_string_position().c_str(),size,get_string_direction().c_str(),hopLength,get_string_status().c_str());
}


Hopper::~Hopper() {
}



