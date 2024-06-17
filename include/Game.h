#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Dino.h"
#include "Obstacle.h"
#include "Score.h"

class Game {
private:
    Dino* dino;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    Score* score;

public:
    Game();
    ~Game();

    void addObstacle(std::shared_ptr<Obstacle> obstacle);
    void update();
    bool checkCollision();
    int getScore() const;
};

#endif // GAME_H
