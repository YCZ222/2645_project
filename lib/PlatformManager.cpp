#include "PlatformManager.h"
#include <algorithm> 

// Static variables for controlling placement and dynamics of platforms.
static int last_x = 81;
static int last_y = 40;
int y_variation = 14;
int x_distance = 10;
int consecutive_top = 0;
int consecutive_bottom = 0;

// Constructor: Initializes platforms with starting configurations.
PlatformManager::PlatformManager() : spawnCounter(0) {
    int initial_y_variation = 5;
    for (int i = 0; i < MAX_PLATFORMS; i++) {
        int new_y = last_y + (rand() % (2 * initial_y_variation + 1) - initial_y_variation);
        new_y = std::max(std::min(new_y, 40), 10);  // Ensure new_y stays within vertical bounds.
        platforms[i] = Platform(81, 15, new_y);
        platforms[i].deactivate();
        last_y = new_y;  // Update the last_y for consistent vertical placement.
    }
}

// Update function: Manages dynamic placement and reactivation of platforms.
void PlatformManager::update(float dt) {
    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        platforms[i].update(dt);
        if (platforms[i].get_x() < -platforms[i].get_width()) {  // Check if the platform has moved off-screen.
            int new_y = last_y + (rand() % (2 * y_variation + 1) - y_variation);
            // Enforce gameplay mechanics to avoid repetitive patterns at screen boundaries.
            // Check and manage consecutive placement at boundaries
            // Check and manage consecutive placement at boundaries
                if (new_y >= 40) {
                    consecutive_top++;
                    consecutive_bottom = 0; // Reset the other boundary's count
                    if (consecutive_top >= 3) {
                        new_y = 30; // Force downwards if too many at top
                        consecutive_top = 0; // Reset
                    }
                } else if (new_y <= 10) {
                    consecutive_bottom++;
                    consecutive_top = 0; // Reset the other boundary's count
                    if (consecutive_bottom >= 3) {
                        new_y = 20; // Force upwards if too many at bottom
                        consecutive_bottom = 0; // Reset
                    }
                } else {
                    // Reset both if a new platform is within normal range
                    consecutive_top = 0;
                    consecutive_bottom = 0;
                }

            new_y = std::max(std::min(new_y, 40), 10);  // Reinforce vertical bounds.
            platforms[i].activate(81 + x_distance, 15, new_y);
            last_x = 81 + x_distance;  // Update last_x to position the next platform.
            last_y = new_y;  // Update last_y for vertical consistency.
        }
    }

    if (++spawnCounter >= 20) {
        spawnCounter = 0;
        generate();  // Generate new platforms if needed.
    }
}

// Draw function: Renders active platforms on the LCD display.
void PlatformManager::draw(N5110 &lcd) {
    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (platforms[i].is_active() && platforms[i].get_x() + platforms[i].get_width() > 0) {
            int drawX = (platforms[i].get_x() < 0) ? 0 : platforms[i].get_x();
            int visibleWidth = (platforms[i].get_x() < 0) ? platforms[i].get_width() + platforms[i].get_x() : platforms[i].get_width();
            if (visibleWidth > 0) {
                lcd.drawRect(drawX, platforms[i].get_y(), visibleWidth, 1.0f, FILL_BLACK);
            }
        }
    }
}

// Generate function: Activates a deactivated platform with new characteristics.
void PlatformManager::generate() {
    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (!platforms[i].is_active()) {
            int new_y = last_y + (rand() % (2 * y_variation + 1) - y_variation);
            new_y = std::max(std::min(new_y, 40), 10);
            platforms[i].activate(last_x + x_distance, 15, new_y);
            last_x += x_distance;
            last_y = new_y;
            break;
        }
    }
}

// isOnPlatform function: Determines if the player is currently on any active platform.
bool PlatformManager::isOnPlatform(float x, float y, float velocity_y) const {
    if (velocity_y <= 0) {
        return false;  // No collision detection if player is moving upwards or stationary in y.
    }

    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (platforms[i].is_active() && y >= platforms[i].get_y() - 2 && y < platforms[i].get_y() &&
            x >= platforms[i].get_x() && x <= platforms[i].get_x() + platforms[i].get_width()) {
            return true;  // Player is considered to be on the platform.
        }
    }
    return false;
}

// findPlatformY function: Finds the y-coordinate of the platform at a given x-coordinate, if any.
float PlatformManager::findPlatformY(float x) const {
    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (platforms[i].is_active() && x >= platforms[i].get_x() && x <= platforms[i].get_x() + platforms[i].get_width()) {
            return platforms[i].get_y();  // Return the y-coordinate of the platform.
        }
    }
    return -1;  // No platform found at the given x-coordinate.
}
