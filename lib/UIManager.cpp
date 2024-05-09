#include "UIManager.h"
#include <sstream>

UIManager::UIManager(N5110 &lcd, Joystick &joystick, DigitalIn &buttonStart, DigitalIn &buttonSelect)
    : lcd(lcd), joystick(joystick), buttonStart(buttonStart), buttonSelect(buttonSelect) {}

void UIManager::showWelcomeScreen() {
    lcd.clear();
    lcd.drawSprite(0, 1, 16, 10, (int*)figure1);   
    lcd.drawSprite(84 - 10, 1, 16, 10, (int*)figure2); 
    lcd.drawRect(18, 13, 15, 1, FILL_BLACK);
    lcd.drawRect(35, 5, 15, 1, FILL_BLACK);
    lcd.drawRect(50, 10, 15, 1, FILL_BLACK);
    lcd.printString("   Running!  ", 1, 2);
    lcd.printString(" ============ ", 0, 3);
    lcd.printString("Press Nucleo", 0, 4);
    lcd.printString("Blue button", 0, 5);
    
    lcd.refresh();


    while (buttonStart.read() == 1) {
        ThisThread::sleep_for(100ms); 
    }

   
    lcd.clear();
    lcd.printString("Loading...", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(1000ms);  
}


void UIManager::instructionScreen(){
    lcd.printString(" Instruction  ", 1, 0);
    lcd.printString(" Button:jump", 0, 1);
    lcd.printString(" Joystick:", 0, 2);
    lcd.printString(" left&right", 0, 3);
    lcd.printString("  stay on", 0, 4);
    lcd.printString("  platform!!", 0, 5);
    lcd.refresh();
    while (buttonSelect.read() == 1) {
        ThisThread::sleep_for(100ms); 
    }
    lcd.clear();
    ThisThread::sleep_for(300ms); 
    
}


int UIManager::getDifficultyChoice() {
    int y_pos = 0; 
    bool selected = false;

    lcd.clear();
    lcd.printString("Choose", 0, 0);
    lcd.printString("Difficulty:", 0, 1);
    lcd.printString("> Normal", 0, 3);
    lcd.printString("  Hard", 0, 4);
    lcd.refresh();

    while (!selected) {
        if (joystick.get_direction() == S && y_pos > 0) {
            y_pos--;
            updateDisplay(y_pos);
        }
        if (joystick.get_direction() == N && y_pos < 1) {
            y_pos++;
            updateDisplay(y_pos);
        }
        if (buttonSelect.read() == 0) { 
            selected = true;
        }
        ThisThread::sleep_for(100ms);
    }

    return y_pos + 1; // Return 1 for Normal, 2 for Hard
}

void UIManager::updateDisplay(int y_pos) {
    lcd.clear();
    lcd.printString("Choose", 0, 0);
    lcd.printString("Difficulty:", 0, 1);
    lcd.printString(y_pos == 0 ? "> Normal" : "  Normal", 0, 3);
    lcd.printString(y_pos == 1 ? "> Hard" : "  Hard", 0, 4);
    lcd.refresh();
}

void UIManager::showGameOverScreen(int score) {
    lcd.clear();
    lcd.printString("  Game Over  ", 1, 0);
    std::string scoreStr = "Score: " + std::to_string(score);
    lcd.printString(scoreStr.c_str(), 0, 1);
    lcd.printString(" ============ ", 0, 2);
    lcd.printString("Press Nucleo", 0, 3);
    lcd.printString("Black button", 0, 4);
    lcd.printString("to Restart", 0, 5);

    lcd.refresh();
}


const int UIManager::figure1[16][10] = {
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
};

const int UIManager::figure2 [16][10] = {
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
};



