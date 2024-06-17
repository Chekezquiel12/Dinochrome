#include "Obstacle.h"

Obstacle::Obstacle(int pos) : position(pos) {}

void Obstacle::move() {
    position -= 1; // Lógica para mover el obstáculo
}

int Obstacle::getPosition() const {
    return position;
}
