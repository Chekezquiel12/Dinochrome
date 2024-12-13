#ifndef SCORE_HPP
#define SCORE_HPP

class Score {
private:
    int points;

public:
    
    Score() : points(0) {}

    
    void update() {
        points += 1; 
    }

    
    int getPoints() const {
        return points;
    }
};

#endif 
