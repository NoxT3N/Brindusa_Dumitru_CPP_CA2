//
// Created by brind on 11/04/2024.
//

#ifndef BRINDUSA_DUMITRU_CA2_BUG_H
#define BRINDUSA_DUMITRU_CA2_BUG_H

#include <list>
#include <string>

using namespace std;

class Bug {
public:
    enum direction{NORTH,EAST,SOUTH,WEST};
protected:
    int id;
    pair<int,int> position;
    direction dir; // Direction the bug is facing
    int size; // Size of the bug (initially 1-20); biggest bug wins in a fight
    bool alive;
    list<pair<int,int>> path; // Path taken by a bug. (i.e. the List of positions (on grid) that a  bug visited.)

public:
    Bug() = default;
    Bug(int,pair<int,int>,direction,int);

    bool isWayBlocked();

    void changeDirection();

    virtual void move() =0;
    virtual ~Bug();

    string get_string_position();

    string get_string_direction();

    string get_string_status();

    //getters generated by Clion

    [[nodiscard]] int get_id() const {
        return id;
    }

    [[nodiscard]] direction get_dir() const {
        return dir;
    }

    [[nodiscard]] int get_size() const {
        return size;
    }

    [[nodiscard]] bool is_alive() const {
        return alive;
    }

    [[nodiscard]] list<pair<int, int>> get_path() const {
        return path;
    }
};



#endif //BRINDUSA_DUMITRU_CA2_BUG_H
