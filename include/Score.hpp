#ifndef SCORE_H
#define SCORE_H

class Score {
private:
    int points;

public:
    Score();
    void update();
    int getPoints() const;
};

#endif // SCORE_H
