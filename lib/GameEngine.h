
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "Player.h"
#include "ObstacleManager.h"
#include "PlatformManager.h"
#include "UIManager.h"

class GameEngine {
public:
    GameEngine(Joystick &joystick, DigitalIn &button, DigitalIn &buttonA, BusOut &leds, N5110 &lcd);
    float dt;
    void init(BusOut &leds, N5110 &lcd);
    void update();
    void updateLEDs(int health, BusOut &leds);
    void draw(N5110 &lcd);
    void endGame();

private:
    bool isGameOver;
    Joystick &joystick;
    DigitalIn &button;  
    DigitalIn &buttonA; 
    BusOut &leds;
    Player player;
    ObstacleManager obstacleManager;
    PlatformManager platformManager;
    UIManager uiManager;
};

#endif
