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
                position.second--;
                break;
            case SOUTH:
                position.second++;
                break;
            case WEST:
                position.first--;
            break;
            case EAST:
                position.first++;
                break;
        }
        updatePath();
    }
    else {
        changeDirection();
        move();
    }
}


Crawler::~Crawler() {
    cout << "~Crawler() destructor called." <<endl;
}
