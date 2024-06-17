#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
protected:
    int position;

public:
    Obstacle(int pos);
    virtual void move();
    int getPosition() const;
};

#endif // OBSTACLE_H
