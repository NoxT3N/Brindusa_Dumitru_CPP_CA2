//
// Created by brind on 15/04/2024.
//

#ifndef BRINDUSA_DUMITRU_CA2_CRAWLER_H
#define BRINDUSA_DUMITRU_CA2_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {

public:
    Crawler() = default;
    Crawler(int id,pair<int,int> position,direction dir,int size);

    void move() override;

    ~Crawler() override;
};


#endif //BRINDUSA_DUMITRU_CA2_CRAWLER_H
