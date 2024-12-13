#ifndef BIRD_HPP
#define BIRD_HPP

#include "Obstacle.h"


class Bird : public Obstacle {
public:
    
    Bird(int pos) : Obstacle(pos) {}

    
    void move() override {
        Obstacle::move();
       
    }
};

#endif 
