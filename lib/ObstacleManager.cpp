#include "ObstacleManager.h"
#include <algorithm>

ObstacleManager::ObstacleManager() : spawnCounter(0), last_x(81) {
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        obstacles[i] = Obstacle(last_x, 15 + std::rand() % (35 - 15 + 1), 5 + std::rand() % 5, 5 + std::rand() % 5);
        obstacles[i].deactivate(); // Initially set to non-active state
    }
}

void ObstacleManager::update(float dt) {
    for (int i = 0; i < MAX_OBSTACLES; ++i) {
        obstacles[i].update(dt);
        // Reactivate the obstacle with new properties if it moves off the left side of the screen
        if (obstacles[i].get_x() < -obstacles[i].get_width()) {
            int new_y = 15 + std::rand() % (35 - 15 + 1);  // Random y-coordinate within specified range
            int new_width = 5 + std::rand() % 5;  // Random width between 5 and 9
            int new_height = 5 + std::rand() % 5;  // Random height between 5 and 9
            int distance = 10 + std::rand() % 10;  // Random x distance between 10 and 20
            // Calculate new x-position based on the last known x-position of an obstacle
            int new_x = last_x + distance;
            obstacles[i].activate(new_x, new_y, new_width, new_height);
            last_x = new_x;  // Update last_x to the new x-position of this obstacle
        }
    }

    if (++spawnCounter >= 20) {
        spawnCounter = 0;
        generate();
    }
}

void ObstacleManager::draw(N5110 &lcd) {
    for (int i = 0; i < MAX_OBSTACLES; ++i) {
        if (obstacles[i].is_active() && obstacles[i].get_x() + obstacles[i].get_width() > 0) {
            int drawX = (obstacles[i].get_x() < 0) ? 0 : obstacles[i].get_x();
            int visibleWidth = (obstacles[i].get_x() < 0) ? obstacles[i].get_width() + obstacles[i].get_x() : obstacles[i].get_width();
            if (visibleWidth > 0) {
                lcd.drawRect(drawX, obstacles[i].get_y(), visibleWidth, obstacles[i].get_height(), FILL_BLACK);
            }
        }
    }
}

void ObstacleManager::generate() {
    for (int i = 0; i < MAX_OBSTACLES; i++) {
        if (!obstacles[i].is_active()) {
            int new_y = 15 + std::rand() % (35 - 15 + 1);
            int distance = 10 + std::rand() % (20 - 10 + 1);
            obstacles[i].activate(last_x + distance, new_y, 5 + std::rand() % 5, 5 + std::rand() % 5);
            last_x += distance;  // Update last_x for the next obstacle's x-coordinate
            break;
        }
    }
}

