//
// Created by brind on 15/04/2024.
//

#ifndef BRINDUSA_DUMITRU_CA2_HOPPER_H
#define BRINDUSA_DUMITRU_CA2_HOPPER_H

#include "Bug.h"

class Hopper: public Bug {
private:
    int hopLength;
public:
    Hopper() = default;
    Hopper(int id,pair<int,int> position,direction dir,int size,int hopLenght);

    void move() override;

    ~Hopper() override;

    [[nodiscard]] int get_hop_length() const {
        return hopLength;
    }
};


#endif //BRINDUSA_DUMITRU_CA2_HOPPER_H
