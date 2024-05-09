#include "GameEngine.h"

// Constructor: Initializes the GameEngine with provided input and output devices, and other game components
GameEngine::GameEngine(Joystick &joystick, DigitalIn &button, DigitalIn &buttonA, BusOut &leds, N5110 &lcd) 
    : joystick(joystick), button(button), buttonA(buttonA), leds(leds), isGameOver(false), player(), 
    obstacleManager(), platformManager(), uiManager(lcd, joystick, buttonA, button) {}

// init function: Sets up the game environment, initializes devices, and handles the welcome and instruction screens
void GameEngine::init(BusOut &leds, N5110 &lcd) {
    leds.write(0);  // Turn off all LEDs initially
    lcd.init(LPH7366_1);  // Initialize the LCD display with specific driver
    lcd.setContrast(0.5);  // Set LCD contrast
    lcd.setBrightness(0.55);  // Set LCD brightness
    joystick.init();  // Initialize joystick
    uiManager.showWelcomeScreen();  // Display welcome screen
    uiManager.instructionScreen();  // Display instructions screen
    int difficulty = uiManager.getDifficultyChoice();  // Get user's difficulty choice
    if (difficulty == 1) {
        dt = 1.0;  // Set slower game speed
        player.setHealth(4);  // Set higher health for easier difficulty
    } else if (difficulty == 2) {
        dt = 1.1;  // Set faster game speed
        player.setHealth(3);  // Set lower health for harder difficulty
    }
}

// update function: Manages the main game loop, updating game state and checking game over conditions
void GameEngine::update() {
    if (!isGameOver && player.getHealth() > 0) {
        player.update(joystick, button, platformManager, obstacleManager);  // Update player state
        obstacleManager.update(dt);  // Update obstacles state
        platformManager.update(dt);  // Update platforms state
        updateLEDs(player.getHealth(), leds);  // Update LED indicators based on player health
    }

    if (player.getHealth() <= 0 && !isGameOver) {
        isGameOver = true;  // Set game over condition
        endGame();  // Trigger game over sequence
    }
}

// updateLEDs function: Controls LED indicators based on player's current health
void GameEngine::updateLEDs(int health, BusOut &leds) {
    if (health > 0) {
        int mask = (1 << health) - 1;  // Calculate bitmask for LEDs based on health
        leds.write(15);  // Incorrectly set LEDs to 15, should use 'mask'
    } else {
        leds.write(0);  // Turn off all LEDs if health is zero
    }
}

// draw function: Renders the game graphics on the LCD
void GameEngine::draw(N5110 &lcd) {
    if(!isGameOver){
        lcd.clear();  // Clear LCD display
        player.draw(lcd);  // Draw player
        obstacleManager.draw(lcd);  // Draw obstacles
        platformManager.draw(lcd);  // Draw platforms
        lcd.refresh();  // Refresh LCD display to show updated graphics
    }
}

// endGame function: Handles actions to perform when the game ends
void GameEngine::endGame() {
    int score = player.getScore();  // Retrieve player's final score
    uiManager.showGameOverScreen(score);  // Display game over screen with score
}
