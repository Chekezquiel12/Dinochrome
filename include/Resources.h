#pragma once

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_PGEX_SOUND
#include "olcPGEX_Sound.h"

// Audio
enum AudioSamples {
    GAMEOVER_AUDIO,
    JUMP_AUDIO,
    DIE_AUDIO,
    HIT_AUDIO,
    SCORE_AUDIO,
};

// Sprites
enum Sprites {
    NUMBER,
    CHAR_H = 10,
    CHAR_I,
    ARROW,
    CACTUS = 12,
    CLOUD = 22,
    DINO,
    GAMEOVER = 32,
    GROUND,
    PTERANODON = 33,
    SPRITES = 36,
};

// Definiciones adicionales
#define SCORE_DIGITS 5
#define PLAYER_POSITION 60.0f
#define JUMP_MULTIPLIER 15
#define GROUND_SPEED 500.0f
