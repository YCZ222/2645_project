#include "Player.h"

Player::Player() : x(1), y(45), velocityY(0), isJumping(false) {}

void Player::update(Joystick &joystick, DigitalIn &button, PlatformManager &platformManager) {
    // Move player based on joystick direction
    if (joystick.get_direction() == E) {
        x--;
    } else if (joystick.get_direction() == W) {
        x++;
    }

    // Jumping logic
    if (!isJumping && button.read() == 0) {
        isJumping = true;
        velocityY = JUMP_HEIGHT;
    }

    if (isJumping) {
        y += velocityY;
        velocityY += GRAVITY; 
        if (y >= 40) {
            y = 40;
            isJumping = false;
        }
    }


    
    // Gravity logic
    if (!isOnPlatform(x, y, velocityY, platformManager)) {
    velocityY += GRAVITY;
    y += velocityY;

    // 如果玩家向下移动并且落在平台上，停止下落并调整位置
        if (velocityY > 0 && isOnPlatform(x, y, velocityY, platformManager)) {
        velocityY = 0;
        y = findPlatformY(x, platformManager) - 2;  // 将玩家位置调整至平台顶部
        isJumping = false;
    }
}
    else {
    // 如果玩家已经在平台上，则重置垂直速度并调整位置
    velocityY = 0;
    y = findPlatformY(x, platformManager) - 2;
    isJumping = false;
}

    checkBoundary();
}

void Player::draw(N5110 &lcd) {
    lcd.drawRect(x, y, 2, 2, FILL_BLACK); // Drawing the player
}



bool Player::isOnPlatform(float x, float y, float velocityY, PlatformManager &platformManager) {
    return platformManager.isOnPlatform(x, y, velocityY);
}

float Player::findPlatformY(float x, PlatformManager &platformManager) {
    return platformManager.findPlatformY(x);
}

void Player::checkBoundary() {
     if (x < 1 ){        //ensure that the point doesnt pass beyond the left hand side of the screen
        x = 1;
    }else if (x > 81){  //ensure that the point doesnt pass beyond the right hand side of the screen-
        x = 81;
    }

    if(y < 1){          //ensure that the point doesnt pass beyond the top of the screen
        y = 1;
    }else if(y > 45){   //ensure that the point doesnt pass beyond the bottom of the screen
        y = 45;
    }
}
