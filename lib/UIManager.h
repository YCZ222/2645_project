#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"

class UIManager {
public:
    UIManager(N5110 &lcd, Joystick &joystick, DigitalIn &buttonStart, DigitalIn &buttonSelect);
    void showWelcomeScreen();
    void instructionScreen();
    int getDifficultyChoice();
    void updateDisplay(int y_pos);
    void showGameOverScreen(int score);
    
private:
    static const int figure1[16][10]; 
    static const int figure2[16][10];
    N5110 &lcd;
    Joystick &joystick;
    DigitalIn &buttonStart;   
    DigitalIn &buttonSelect;  
};


#endif
