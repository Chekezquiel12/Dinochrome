#ifndef CACTUS_HPP
#define CACTUS_HPP

#include "Obstacle.h"


class Cactus : public Obstacle {
public:
   
    Cactus(int pos) : Obstacle(pos) {}

    
    void move() override {
        Obstacle::move();
       
    }
};

#endif 
