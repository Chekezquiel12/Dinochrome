#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "DinoGame.h"

int main() {
    DinoGame demo;
    if (demo.Construct(1100, 320, 1, 1))
        demo.Start();

    return 0;
}
