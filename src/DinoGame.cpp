#include "DinoGame.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>

DinoGame::DinoGame() {
    sAppName = "Dino Game";
}

bool DinoGame::OnUserCreate() {
    screenWidth = ScreenWidth();
    screenHeight = ScreenHeight();

    std::filesystem::path dir(std::filesystem::current_path().string());
    std::filesystem::path spriteDir("assets/sprites");
    std::filesystem::path audioDir("assets/audio");

    olc::SOUND::InitialiseAudio(44100, 1, 8, 512);

    std::vector<std::string> files;
    for (const auto& file : std::filesystem::directory_iterator(dir / audioDir)) {
        files.push_back(file.path().string());
    }

    std::sort(files.begin(), files.end());
    for (const auto& file : files) {
        int id = olc::SOUND::LoadAudioSample(file);
        if (id == -1) throw std::runtime_error("Failed to load audio sample: " + file);
        sounds.push_back(id);
    }

    files.clear();
    for (const auto& file : std::filesystem::directory_iterator(dir / spriteDir)) {
        files.push_back(file.path().string());
    }

    std::sort(files.begin(), files.end());
    for (const auto& file : files) {
        olc::Sprite* sprite = new olc::Sprite(file);
        if (sprite == nullptr) throw std::runtime_error("Failed to load sprite: " + file);
        sprites.push_back(new olc::Decal(sprite));
    }

    delete sprites[DINO + 0]->sprite;
    delete sprites[DINO + 0];
    delete sprites[SPRITES]->sprite;
    delete sprites[SPRITES];

    srand(std::time(0));

    return true;
}

bool DinoGame::OnUserUpdate(float fElapsedTime) {
    Clear(olc::Pixel(230, 230, 230));

    float elapsedTime = gameOver ? 0.0f : fElapsedTime;
    DrawScore(elapsedTime);
    DrawGround(elapsedTime);
    DrawClouds(elapsedTime);
    DrawEnemies(elapsedTime);

    elapsed += fElapsedTime;
    if (elapsed > period * 3.0f) {
        elapsed = 0.0f;
        if (gameOver) {
            dinoIndex = 6;
        } else if (isJumping) {
            dinoIndex = 1;
        } else if (isDucking) {
            dinoIndex = dinoIndex == 7 ? 8 : 7;
        } else if (started) {
            dinoIndex = dinoIndex == 3 ? 4 : 3;
        } else {
            dinoIndex = rand() % 15 ? 1 : 2;
        }

        if (started && !gameOver) {
            score++;
            if (score > 0 && score % 100 == 0) {
                olc::SOUND::PlaySample(sounds[SCORE_AUDIO]);
            }
        }
    }

    olc::Decal* dino = sprites[DINO + dinoIndex];
    int dinoWidth = dino->sprite->width;
    int dinoHeight = dino->sprite->height;
    int maxJumpHeight = dinoHeight * JUMP_MULTIPLIER;
    float jumpParabola = -maxJumpHeight * (jumpTimer * jumpTimer - jumpDuration * jumpTimer);
    position.x = PLAYER_POSITION;
    position.y = std::max(screenHeight - dinoHeight - 8 - jumpParabola, 0.0f);
    DrawDecal(position, dino);

    if (GetKey(olc::Key::SPACE).bPressed) {
        if (!started) {
            gameOver = false;
            started = true;
            enemies.clear();
        }
        if (started) {
            isJumping = true;
            if (jumpTimer == 0.0f) {
                olc::SOUND::PlaySample(sounds[JUMP_AUDIO]);
            }
        }
    }

    if (isJumping && !gameOver) {
        jumpTimer += fElapsedTime;
        if (jumpTimer > jumpDuration) {
            isJumping = false;
            jumpTimer = 0.0f;
        }
    }

    if (GetKey(olc::Key::DOWN).bPressed && started) isDucking = true;
    if (GetKey(olc::Key::DOWN).bReleased) isDucking = false;

    if (gameOver) {
        olc::Decal* gameOverSprite = sprites[GAMEOVER];
        olc::vf2d gameOverPos = {
            float(screenWidth / 2 - gameOverSprite->sprite->width / 2),
            float(screenHeight / 2 - gameOverSprite->sprite->height / 2 - screenHeight / 6)
        };
        DrawDecal(gameOverPos, gameOverSprite);
        olc::Decal* arrowSprite = sprites[ARROW];
        olc::vf2d arrowPos = {
            float(screenWidth / 2 - arrowSprite->sprite->width / 2),
            float(screenHeight / 2 - arrowSprite->sprite->height / 2 + screenHeight / 10)
        };
        DrawDecal(arrowPos, arrowSprite);
    } else {
        for (auto& enemy : enemies) {
            float ex0 = enemy.pos.x;
            float ey0 = enemy.pos.y;
            float ex1 = enemy.pos.x + enemy.width;
            float ey1 = enemy.pos.y + enemy.height;

            float px0 = position.x;
            float py0 = position.y;
            float px1 = position.x + dinoWidth;
            float py1 = position.y + dinoHeight;

            if (px0 > ex1) break;

            bool noOverlap = ex0 > px1 || px0 > ex1 || ey0 > py1 || py0 > ey1;
            if (!noOverlap) {
                gameOver = true;
                isJumping = false;
                isDucking = false;
                started = false;

                maxScore = std::max(score, maxScore);
                score = 0;

                olc::SOUND::PlaySample(sounds[GAMEOVER_AUDIO]);
            }
        }
    }

    return true;
}
void DinoGame::LoadResources() {
    // Cargar imágenes
    sprites.resize(SPRITES);
    sprites[DINO] = new olc::Decal(new olc::Sprite("resources/sprites/dino.png"));
    sprites[GROUND] = new olc::Decal(new olc::Sprite("resources/sprites/ground.png"));
    sprites[CACTUS] = new olc::Decal(new olc::Sprite("resources/sprites/cactus.png"));
    sprites[CLOUD] = new olc::Decal(new olc::Sprite("resources/sprites/cloud.png"));
    sprites[PTERANODON] = new olc::Decal(new olc::Sprite("resources/sprites/pteranodon.png"));
    for (int i = 0; i < 10; i++) {
        sprites[NUMBER + i] = new olc::Decal(new olc::Sprite("resources/sprites/numbers/" + std::to_string(i) + ".png"));
    }
    sprites[GAMEOVER] = new olc::Decal(new olc::Sprite("resources/sprites/gameover.png"));
    sprites[ARROW] = new olc::Decal(new olc::Sprite("resources/sprites/arrow.png"));

    // Cargar audio
    sounds.resize(SCORE_AUDIO + 1);
    sounds[JUMP_AUDIO] = olc::SOUND::LoadAudioSample("resources/audio/jump.wav");
    sounds[DIE_AUDIO] = olc::SOUND::LoadAudioSample("resources/audio/die.wav");
    sounds[HIT_AUDIO] = olc::SOUND::LoadAudioSample("resources/audio/hit.wav");
    sounds[SCORE_AUDIO] = olc::SOUND::LoadAudioSample("resources/audio/score.wav");
}

void DinoGame::DrawScore(float elapsedTime) {
    if (score >= 1000) {
        if (scoreBlinking) {
            scoreTimer += elapsedTime;
            if (scoreTimer >= 0.25f) {
                scoreTimer = 0.0f;
                scoreBlinking = false;
            }
        } else {
            scoreTimer += elapsedTime;
            if (scoreTimer >= 0.25f) {
                scoreTimer = 0.0f;
                scoreBlinking = true;
            }
        }
    }

    int x = screenWidth - 40;
    int y = 20;

    int n = score;
    for (int i = 0; i < SCORE_DIGITS; i++) {
        int digit = n % 10;
        n /= 10;

        if (!(score >= 1000 && scoreBlinking)) {
            DrawDecal({ float(x), float(y) }, sprites[NUMBER + digit]);
        }
        x -= 10;
    }

    x -= 20;
    n = maxScore;
    for (int i = 0; i < SCORE_DIGITS; i++) {
        int digit = n % 10;
        n /= 10;
        DrawDecal({ float(x), float(y) }, sprites[NUMBER + digit]);
        x -= 10;
    }
    DrawDecal({ float(x), float(y) }, sprites[CHAR_I]);
    DrawDecal({ float(x - 10), float(y) }, sprites[CHAR_H]);
}

void DinoGame::DrawGround(float elapsedTime) {
    static std::vector<olc::vf2d> ground;
    if (!ground.size()) {
        olc::vf2d pos = { 0, screenHeight - 18.0f };
        for (int i = 0; i < screenWidth; i += sprites[GROUND]->sprite->width) {
            ground.push_back(pos);
            pos.x += sprites[GROUND]->sprite->width;
        }
    }

    for (auto& g : ground) {
        g.x -= groundSpeed * elapsedTime;
    }

    while (ground.front().x < -sprites[GROUND]->sprite->width) {
        olc::vf2d g = ground.front();
        g.x = ground.back().x + sprites[GROUND]->sprite->width;
        ground.push_back(g);
        ground.erase(ground.begin());
    }

    for (auto g : ground) {
        DrawDecal(g, sprites[GROUND]);
    }

    groundSpeed = GROUND_SPEED + score;
    if (groundSpeed > maxGroundSpeed) {
        groundSpeed = maxGroundSpeed;
    }
}

void DinoGame::DrawClouds(float elapsedTime) {
    if (clouds.empty()) {
        for (int i = 0; i < 5; i++) {
            float x = rand() % screenWidth;
            float y = rand() % (screenHeight - screenHeight / 2);
            clouds.push_back({ x, y });
        }
    }

    for (auto& cloud : clouds) {
        cloud.x -= cloudSpeed * elapsedTime;
    }

    while (clouds.front().x < -sprites[CLOUD]->sprite->width) {
        olc::vf2d cloud = clouds.front();
        cloud.x = screenWidth + sprites[CLOUD]->sprite->width;
        cloud.y = rand() % (screenHeight - screenHeight / 2);
        clouds.push_back(cloud);
        clouds.erase(clouds.begin());
    }

    for (auto& cloud : clouds) {
        DrawDecal(cloud, sprites[CLOUD]);
    }
}

void DinoGame::DrawEnemies(float elapsedTime) {
    if (!started) return;

    if (enemies.empty() || enemies.back().pos.x < screenWidth / 2) {
        enemy e;
        e.type = rand() % 3;
        e.index = 0;

        if (e.type == 0) {
            e.width = sprites[CACTUS + 0]->sprite->width;
            e.height = sprites[CACTUS + 0]->sprite->height;
        } else if (e.type == 1) {
            e.width = sprites[CACTUS + 4]->sprite->width;
            e.height = sprites[CACTUS + 4]->sprite->height;
        } else {
            e.width = sprites[PTERANODON + 0]->sprite->width;
            e.height = sprites[PTERANODON + 0]->sprite->height;
        }

        e.pos.x = screenWidth + e.width;
        e.pos.y = screenHeight - e.height - 8;
        enemies.push_back(e);
    }

    for (auto& enemy : enemies) {
        enemy.pos.x -= groundSpeed * elapsedTime;
        if (enemy.type == 2) {
            pteranodonTimer += elapsedTime;
            if (pteranodonTimer > 0.1f) {
                enemy.index = enemy.index == 0 ? 1 : 0;
                pteranodonTimer = 0.0f;
            }
        }
    }

    while (enemies.front().pos.x < -sprites[enemies.front().type == 2 ? PTERANODON : CACTUS]->sprite->width) {
        enemies.erase(enemies.begin());
    }

    for (auto& enemy : enemies) {
        if (enemy.type == 0) {
            DrawDecal(enemy.pos, sprites[CACTUS + 0]);
        } else if (enemy.type == 1) {
            DrawDecal(enemy.pos, sprites[CACTUS + 4]);
        } else {
            DrawDecal(enemy.pos, sprites[PTERANODON + enemy.index]);
        }
    }
}
