#pragma once

#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"
#include <vector>
#include "Resources.h"
#include <filesystem>

class DinoGame : public olc::PixelGameEngine {
public:
    DinoGame();

private:
    int screenWidth;
    int screenHeight;

    float time;
    float groundSpeed;
    float maxGroundSpeed;
    float cloudSpeed;
    float fps;
    float period;
    float elapsed;
    int dinoIndex;

    float jumpDuration;

    bool started;
    bool isJumping;
    bool isDucking;
    bool gameOver;

    float jumpTimer;
    float pteranodonTimer;

    bool scoreBlinking;
    float scoreTimer;

    int maxScore;
    int score;

    struct enemy {
        int width;
        int height;
        int index;
        int type;
        olc::vf2d pos;
    };

    olc::vf2d position;
    std::vector<olc::Decal*> sprites;
    std::vector<olc::vf2d> clouds;
    std::vector<enemy> enemies;

    std::vector<int> sounds;

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
    bool OnUserDestroy() override;

private:
    void LoadResources();
    void DrawScore(float fElapsedTime);
    void DrawNumber(int num, int offset, int pad);
    void DrawGround(float fElapsedTime);
    void DrawEnemies(float fElapsedTime);
    void AddPteranodon();
    void AddCactus();
    void DrawClouds(float fElapsedTime);
};

