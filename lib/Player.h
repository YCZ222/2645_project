#ifndef PLAYER_H
#define PLAYER_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "PlatformManager.h" // 用于判断是否在平台上

class Player {
public:
    Player();
    void update(Joystick &joystick, DigitalIn &button, PlatformManager &platformManager);
    void draw(N5110 &lcd);

private:
    float x, y;
    float velocityY;
    bool isJumping;
    static constexpr float GRAVITY = 0.15f;
    static constexpr float JUMP_HEIGHT = -2.0f;

    bool isOnPlatform(float x, float y, float velocity_y, PlatformManager &platformManager);
    float findPlatformY(float x, PlatformManager &platformManager);
    void checkBoundary();
};

#endif
