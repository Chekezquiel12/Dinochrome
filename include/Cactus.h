#ifndef CACTUS_H
#define CACTUS_H

#include "Obstacle.h"

class Cactus : public Obstacle {
public:
    Cactus(int pos);
    void move() override;
};

#endif // CACTUS_H
