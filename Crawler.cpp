//
// Created by brind on 15/04/2024.
//

#include "Crawler.h"
#include <iostream>

using namespace std;

Crawler::Crawler(int id, pair<int, int> position, direction dir, int size) : Bug(id, position, dir, size) {};


void Crawler::move() {
    if(Crawler::isWayBlocked()!= true) {
        switch(dir) {
            case NORTH:
                position.first--;
                break;
            case SOUTH:
                position.first++;
                break;
            case WEST:
                position.second--;
            break;
            case EAST:
                position.second++;
                break;
        }
        updatePath();
    }
    else {
        changeDirection();
        move();
    }
}

void Crawler::displayBug() {
    printf("%-4d %-8s %-10s %-5d %-10s %15s\n",id,"Crawler",get_string_position().c_str(),size,get_string_direction().c_str(),get_string_status().c_str());
}


Crawler::~Crawler() {
    cout << "~Crawler() destructor called." <<endl;
}
