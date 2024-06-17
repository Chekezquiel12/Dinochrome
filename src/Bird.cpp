#include "Bird.h"

Bird::Bird(int pos) : Obstacle(pos) {}

void Bird::move() {
    Obstacle::move();
    // Lógica específica para Bird
}
