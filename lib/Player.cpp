#include "Player.h"
#include <chrono>

using namespace std::chrono;

// Constructor: Initializes player properties.
Player::Player() : x(1), y(45), velocityY(0), isJumping(false), health(4), invincible(false), firstPlatformTouched(false) {}

// Update function: Manages player's movement, jumping, health, and collisions.
void Player::update(Joystick &joystick, DigitalIn &button, PlatformManager &platformManager, ObstacleManager &obstacleManager) {
    // Manage invincibility timer.
    if (invincible && duration_cast<milliseconds>(invincibleTimer.elapsed_time()).count() >= INVINCIBILITY_TIME) {
        invincible = false;
        invincibleTimer.stop();
        invincibleTimer.reset();
    }

    // Lateral movement logic based on joystick direction.
    if (joystick.get_direction() == E) {
        x--;
    } else if (joystick.get_direction() == W) {
        x++;
    }

    // Jumping logic: Initiates jump if not already jumping and button is pressed.
    if (!isJumping && button.read() == 0) {
        isJumping = true;
        velocityY = JUMP_HEIGHT;
    }

    // Apply gravity if jumping.
    if (isJumping) {
        y += velocityY;
        velocityY += GRAVITY;
        if (y >= 40) { // Ground contact logic.
            y = 40;
            isJumping = false;
        }
    }

    // Gravity effect when not on a platform.
    if (!isOnPlatform(x, y, velocityY, platformManager)) {
        velocityY += GRAVITY;
        y += velocityY;

        // Check for landing on a platform after falling.
        if (velocityY > 0 && isOnPlatform(x, y, velocityY, platformManager)) {
            velocityY = 0;
            y = findPlatformY(x, platformManager) - 2;
            isJumping = false;
            if (!firstPlatformTouched) {
                firstPlatformTouched = true;
                scoreTimer.start();
            }
        }
    } else if (isOnPlatform(x, y, velocityY, platformManager)) {
        // Reset velocity and adjust position when on a platform.
        velocityY = 0;
        y = findPlatformY(x, platformManager) - 2;
        isJumping = false;
        if (!firstPlatformTouched) {
            firstPlatformTouched = true;
            scoreTimer.start();
        }
    }

    // Check if the player has fallen to the bottom and handle health and invincibility.
    if (y >= 45 && firstPlatformTouched) {
        if (!invincible) {
            health -= 1;
            invincible = true;
            invincibleTimer.start();
            y = findPlatformY(x, platformManager) - 2;
            if (health <= 0) {
                scoreTimer.stop();
            }
        }
    }

    // Handle collisions with obstacles.
    if (!invincible && checkPlayerCollision(x, y, obstacleManager)) {
        health -= 1;
        invincible = true;
        invincibleTimer.start();
        if (health <= 0) {
            scoreTimer.stop();
        }
    }

    // Check if the player is within the game boundaries.
    checkBoundary();
}

// Draw function: Renders the player on the display, with a flashing effect if invincible.
void Player::draw(N5110 &lcd) {
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);
    if (!invincible || (duration_cast<milliseconds>(invincibleTimer.elapsed_time()).count() / 500) % 3 < 2) {
        lcd.drawRect(x, y, 2, 2, FILL_BLACK);  // Draw the player with flashing effect
    }
}

// Setter and getter for health.
void Player::setHealth(int h) {
    health = h;
}

int Player::getHealth() const {
    return health;
}

// Returns the player's score based on the duration of the score timer.
int Player::getScore() const {
    return duration_cast<seconds>(scoreTimer.elapsed_time()).count();
}

// Boundary check to ensure the player does not move outside the screen area.
void Player::checkBoundary() {
    if (x < 1) {
        x = 1;
    } else if (x > 81) {
        x = 81;
    }

    if (y < 1) {
        y = 1;
    } else if (y > 45) {
        y = 45;
    }
}

// Utility functions to interact with the platform manager for collision and position checks.
bool Player::isOnPlatform(float x, float y, float velocityY, PlatformManager &platformManager) {
    return platformManager.isOnPlatform(x, y, velocityY);
}

float Player::findPlatformY(float x, PlatformManager &platformManager) {
    return platformManager.findPlatformY(x);
}

// Interaction with the obstacle manager to check for collisions with obstacles.
bool Player::checkPlayerCollision(float x, float y, ObstacleManager &obstacleManager) {
    return obstacleManager.checkPlayerCollision(x, y);
}
