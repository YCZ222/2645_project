#include "GameEngine.h"

GameEngine::GameEngine(Joystick &joystick, DigitalIn &button) 
    : joystick(joystick), button(button), player(), obstacleManager(), platformManager() {}

void GameEngine::init(N5110 &lcd) {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.5);
    lcd.setBrightness(0.55);
    joystick.init();
}

void GameEngine::update() {
    player.update(joystick, button, platformManager);
    obstacleManager.update(1.0);  // Assume a fixed time step
    platformManager.update(1.0);  // Assume a fixed time step
}

void GameEngine::draw(N5110 &lcd) {
    lcd.clear();
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    player.draw(lcd);
    obstacleManager.draw(lcd);
    platformManager.draw(lcd);
    lcd.refresh();
}
