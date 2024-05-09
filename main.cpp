#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "GameEngine.h"

// Hardware setup
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_3, PC_2);
DigitalIn button(PC_13);
DigitalIn buttonA(BUTTON1);
BusOut leds(PC_0,PC_1,PB_0,PA_4);
GameEngine game(joystick, button, buttonA, leds, lcd);

int main() {
    game.init(leds, lcd);  
    while (1) {
        game.update();  
        game.draw(lcd);  
        ThisThread::sleep_for(30ms);  
    }
}
