#ifndef DINO_H
#define DINO_H

class Obstacle;

class Dino {
private:
    int position;
    bool isJumping;

public:
    Dino();
    void jump();
    bool collidesWith(const Obstacle& obstacle);
};

#endif // DINO_H
