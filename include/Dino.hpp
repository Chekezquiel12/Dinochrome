#ifndef DINO_HPP
#define DINO_HPP

#include "Obstacle.h"

class Dino {
private:
    int position;
    bool isJumping;

public:
    
    Dino() : position(0), isJumping(false) {}

    
    void jump() {
        if (!isJumping) {
            isJumping = true;
          
        }
    }

    
    bool collidesWith(const Obstacle& obstacle) {
        // Lógica para detectar colisiones
        return false;
    }
};

#endif 
