#include "Score.h"

Score::Score() : points(0) {}

void Score::update() {
    points += 1; // Incrementa la puntuación con el tiempo
}

int Score::getPoints() const {
    return points;
}
