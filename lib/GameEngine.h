#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "Obstacle.h"
#include "Platform.h"


static constexpr int MAX_PLATFORMS = 5;
static constexpr int MAX_OBSTACLES = 2;
class GameEngine {
public:
    GameEngine(Joystick &joystick, DigitalIn &button);
    void init(N5110 &lcd);
    void update();
    void draw(N5110 &lcd);

private:
    Joystick &joystick;
    DigitalIn &button;
    float player_x, player_y;
    bool is_jumping;
    float velocity_y;
    static constexpr float GRAVITY = 0.15f;
    static constexpr float JUMP_HEIGHT = -2.0f;
    Obstacle obstacles[MAX_OBSTACLES];  // 使用数组管理障碍物
    Platform platforms[MAX_PLATFORMS];  // 使用数组管理平台
    int obstacle_spawn_counter;
    int platform_spawn_counter;
    void generate_obstacle();
    void recycle_obstacle(Obstacle* obs);
    void generate_platform();
    void recycle_platform(Platform* plat);
    bool isOnPlatform(float x, float y);
    float findPlatformY(float x);
    void boundary(int x, int y);
};

#endif
