//
// Created by brind on 11/04/2024.
//
#include <iostream>
#include "Bug.h"
#include <chrono>
#include <random>

Bug::Bug(int id,pair<int,int> position,direction dir,int size){
    this->id = id;
    this->position = position;
    this->dir = dir;
    this->size = size;
    alive = true;

}


bool Bug::isWayBlocked() {
    int row = position.first;
    int col = position.second;

    if((dir == direction::NORTH && row-1 != -1 )||
        (dir == direction::SOUTH && row+1 != 10)||
        (dir == direction::WEST && col-1 != -1)||
        (dir == direction::EAST && col+1 != 10)) {
        return false;
    }
    else {
        return true;
    }
}

void Bug::changeDirection() {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<> dis(1,4);

    int randNum = dis(gen);

    switch (randNum) {
        case 1:
            dir = NORTH;
        break;
        case 2:
            dir = SOUTH;
        break;
        case 3:
            dir = WEST;
        break;
        case 4:
            dir = EAST;
        break;
    }
}

string Bug::get_string_position() {
    int x = position.first;
    int y = position.second;

    return "("+std::to_string(x)+", "+std::to_string(y)+")";
}

string Bug::get_string_direction() {
    string strDir;

    switch(dir) {
        case NORTH:
            strDir = "NORTH";
            break;
        case SOUTH:
            strDir = "SOUTH";
            break;
        case WEST:
            strDir = "WEST";
            break;
        case EAST:
            strDir = "EAST";
            break;
    }
    return strDir;
}

string Bug::get_string_status() {
    if(is_alive()) {
        return "Alive";
    }
    else {
        return"Dead";
    }
}



Bug::~Bug(){}
