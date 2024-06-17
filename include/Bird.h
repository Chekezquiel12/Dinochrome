#ifndef BIRD_H
#define BIRD_H

#include "Obstacle.h"

class Bird : public Obstacle {
public:
    Bird(int pos);
    void move() override;
};

#endif // BIRD_H
