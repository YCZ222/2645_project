#ifndef PLAYER_H
#define PLAYER_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "PlatformManager.h" 
#include "ObstacleManager.h"

class Player {
public:
    Player();
    void update(Joystick &joystick, DigitalIn &button, PlatformManager &platformManager, ObstacleManager &obstacleManager);
    void draw(N5110 &lcd);
    void setHealth(int h);  
    int getHealth() const;
    void startScoring();  // 当玩家第一次接触到平台时调用
    int getScore() const;  // 获取玩家的得分
    

private:
    float x, y;
    float velocityY;
    bool isJumping;
    int health;  
    bool invincible;  
    Timer invincibleTimer; 
    bool firstPlatformTouched;
    Timer scoreTimer;
    static constexpr float GRAVITY = 0.15f;
    static constexpr float JUMP_HEIGHT = -2.0f;
    static constexpr int INVINCIBILITY_TIME = 3000;

    bool isOnPlatform(float x, float y, float velocity_y, PlatformManager &platformManager);
    float findPlatformY(float x, PlatformManager &platformManager);
    static bool checkCollision(float x1, float y1, float width1, float height1,
                               float x2, float y2, float width2, float height2, ObstacleManager &obstacleManager);
    bool checkPlayerCollision(float x, float y, ObstacleManager &obstacleManager);
    void checkBoundary();
};

#endif
