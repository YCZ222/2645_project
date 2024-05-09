#include "ObstacleManager.h"
#include "Obstacle.h"
#include <algorithm>

// Constructor: Initializes the obstacle manager and pre-creates SpaceJunk and Bullet objects.
ObstacleManager::ObstacleManager() : last_x(81), spawnCounter(0) {
    // Initialize SpaceJunks with random positions and sizes, then deactivate them.
    for (int i = 0; i < 2; i++) {
        spaceJunks[i] = SpaceJunk(last_x, 15 + std::rand() % (35 - 15 + 1), 5 + std::rand() % 5, 5 + std::rand() % 5);
        spaceJunks[i].deactivate();
    }

    // Initialize Bullets with random positions, then deactivate them.
    for (int i = 0; i < 5; i++) {
        bullets[i] = Bullet(last_x, 11 + std::rand() % (39 - 11 + 1), 4, 1);
        bullets[i].deactivate();
    }
}

// Update function: Manages the repositioning and activation of obstacles.
void ObstacleManager::update(float dt) {
    // Update and potentially reset position of SpaceJunk.
    for (int i = 0; i < 2; i++) {
        spaceJunks[i].update(dt);
        if (spaceJunks[i].get_x() < -spaceJunks[i].get_width()) {  // Reset if off screen to the left.
            int new_y = 15 + std::rand() % (35 - 15 + 1);
            spaceJunks[i].activate(last_x, new_y, 5 + std::rand() % 5, 5 + std::rand() % 5);
            last_x = spaceJunks[i].get_x();
        }
    }

    // Update and potentially reset position of Bullets.
    for (int i = 0; i < 5; i++) {
        bullets[i].update(dt);
        if (bullets[i].get_x() < -bullets[i].get_width()) {
            int new_y = 11 + std::rand() % (39 - 11 + 1);
            bullets[i].activate(last_x, new_y, 4, 1);
            last_x = bullets[i].get_x();
        }
    }

    // Periodically generate new obstacles.
    if (++spawnCounter >= 40) {
        spawnCounter = 0;
        generate();
    }
}

// Draw function: Renders active obstacles on the LCD display.
void ObstacleManager::draw(N5110 &lcd) {
    // Draw active SpaceJunk objects if part of them is visible on the screen.
    for (int i = 0; i < 2; i++) {
        if (spaceJunks[i].is_active() && spaceJunks[i].get_x() + spaceJunks[i].get_width() > 0) {
            int drawX = (spaceJunks[i].get_x() < 0) ? 0 : spaceJunks[i].get_x();
            int visibleWidth = (spaceJunks[i].get_x() < 0) ? spaceJunks[i].get_width() + spaceJunks[i].get_x() : spaceJunks[i].get_width();
            if (visibleWidth > 0) {
                lcd.drawRect(drawX, spaceJunks[i].get_y(), visibleWidth, spaceJunks[i].get_height(), FILL_BLACK);
            }
        }
    }

    // Draw active Bullet objects similarly.
    for (int i = 0; i < 5; i++) {
        if (bullets[i].is_active() && bullets[i].get_x() + bullets[i].get_width() > 0) {
            int drawX = (bullets[i].get_x() < 0) ? 0 : bullets[i].get_x();
            int visibleWidth = (bullets[i].get_x() < 0) ? bullets[i].get_width() + bullets[i].get_x() : bullets[i].get_width();
            if (visibleWidth > 0) {
                lcd.drawRect(drawX, bullets[i].get_y(), visibleWidth, bullets[i].get_height(), FILL_BLACK);
            }
        }
    }
}

// Generate function: Attempts to activate a deactivated obstacle.
void ObstacleManager::generate() {
    // Activate a SpaceJunk if any is available.
    for (int i = 0; i < 2; i++) {
        if (!spaceJunks[i].is_active()) {
            int new_y = 15 + std::rand() % (35 - 15 + 1);
            int distance = 25 + std::rand() % (20 - 10 + 1);
            spaceJunks[i].activate(last_x + distance, new_y, 5 + std::rand() % 5, 5 + std::rand() % 5);
            last_x += distance;
            return;
        }
    }

    // If no SpaceJunk was activated, try to activate a Bullet.
    for (int i = 0; i < 5; i++) {
        if (!bullets[i].is_active()) {
            int new_y = 11 + std::rand() % (39 - 11 + 1);
            bullets[i].activate(last_x, new_y, 4, 1);
            last_x += 5;
            return;
        }
    }
}

// Check collision: Compares bounding boxes for overlap.
bool ObstacleManager::checkCollision(float x1, float y1, float width1, float height1,
                                     float x2, float y2, float width2, float height2) {
    return !(x1 + width1 < x2 || x2 + width2 < x1 ||
             y1 + height1 < y2 || y2 + height2 < y1);
}

// Check player collision: Determines if the player is colliding with any active obstacle.
bool ObstacleManager::checkPlayerCollision(float x, float y) {
    float playerWidth = 2;
    float playerHeight = 2;

    // Check collision for each active SpaceJunk and Bullet.
    for (int i = 0; i < 2; i++) {
        if (spaceJunks[i].is_active()) {
            if (checkCollision(x, y, playerWidth, playerHeight,
                               spaceJunks[i].get_x(), spaceJunks[i].get_y(),
                               spaceJunks[i].get_width(), spaceJunks[i].get_height())) {
                return true;  
            }
        }
    }

   
    for (int i = 0; i < 5; i++) {
        if (bullets[i].is_active()) {
            if (checkCollision(x, y, playerWidth, playerHeight,
                               bullets[i].get_x(), bullets[i].get_y(),
                               bullets[i].get_width(), bullets[i].get_height())) {
                return true; 
            }
        }
    }

    return false;  
}
