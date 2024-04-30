#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "Player.h"
#include "ObstacleManager.h"
#include "PlatformManager.h"

class GameEngine {
public:
    GameEngine(Joystick &joystick, DigitalIn &button);
    void init(N5110 &lcd);
    void update();
    void draw(N5110 &lcd);

private:
    Joystick &joystick;
    DigitalIn &button;
    Player player;
    ObstacleManager obstacleManager;
    PlatformManager platformManager;
};

#endif
