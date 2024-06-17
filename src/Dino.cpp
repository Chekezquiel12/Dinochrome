#include "Dino.h"
#include "Obstacle.h"

Dino::Dino() : position(0), isJumping(false) {}

void Dino::jump() {
    if (!isJumping) {
        isJumping = true;
        // Lógica para el salto
    }
}

bool Dino::collidesWith(const Obstacle& obstacle) {
    // Lógica para detectar colisiones
    return false;
}
