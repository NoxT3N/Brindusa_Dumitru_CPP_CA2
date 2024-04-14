//
// Created by brind on 11/04/2024.
//

#ifndef BRINDUSA_DUMITRU_CA2_BUG_H
#define BRINDUSA_DUMITRU_CA2_BUG_H


class Bug {
    enum direction{NORTH,EAST,SOUTH,WEST};
private:
    int id;
    direction di;
    int size;
    bool alive;

public:
    Bug();
    Bug(int,direction,int,bool );

    virtual void move() =0;
    bool isWayBlocked();

    virtual ~Bug();

};



#endif //BRINDUSA_DUMITRU_CA2_BUG_H
