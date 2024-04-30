#include "PlatformManager.h"
#include <algorithm> // For std::max and std::min functions


static int last_x = 81; // 初始平台位置
static int last_y = 40; // 初始平台高度
int y_variation = 16;
int x_distance = 10;  // Y轴最大变化设为5单位


PlatformManager::PlatformManager() : spawnCounter(0) {
    for (int i = 0; i < MAX_PLATFORMS; i++) {
    platforms[i] = Platform(81, 15, rand() % 45); // 使用假定的 Platform 构造函数参数
    platforms[i].deactivate(); // 初始时设为非激活状态
}
}

void PlatformManager::update(float dt) {
    for (int i = 0; i < MAX_PLATFORMS; ++i) {
    platforms[i].update(dt);
    if (platforms[i].get_x() < -platforms[i].get_width()) {  // 当平台离开屏幕
        int new_y = last_y + (rand() % (2 * y_variation + 1) - y_variation);
        new_y = std::max(std::min(new_y, 40), 10);  // 再次确保Y坐标在屏幕范围内
        platforms[i].activate(81 + x_distance, 15, new_y);
        last_x = 81 + x_distance;  // 更新last_x为屏幕宽度加上间距
        last_y = new_y;  // 更新last_y为重新激活的平台的 Y 坐标
    }
    }


    if (++spawnCounter >= 20) {
        spawnCounter = 0;
        generate();
    }

}

void PlatformManager::draw(N5110 &lcd) {
    // Draw each platform
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

void PlatformManager::generate() {
    // Draw each platform
     for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (!platforms[i].is_active()) {
            int new_y = last_y + (rand() % (2 * y_variation + 1) - y_variation);
            new_y = std::max(std::min(new_y, 40), 10);  // 保证Y坐标在屏幕范围内

            platforms[i].activate(last_x + x_distance, 15, new_y);  // 25 是平台宽度，可能需要调整为实际宽度
            last_x += x_distance;  // 更新 last_x 为新生成平台的 X 坐标
            last_y = new_y;        // 更新 last_y 为新生成平台的 Y 坐标
            break;
        }
    }
}

bool PlatformManager::isOnPlatform(float x, float y, float velocity_y) const{
    if (velocity_y <= 0) {
        return false;  // 如果玩家在上升或处于最高点，直接返回false，允许穿透平台
    }

    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (platforms[i].is_active() && y >= platforms[i].get_y() - 2 && y < platforms[i].get_y() &&
            x >= platforms[i].get_x() && x <= platforms[i].get_x() + platforms[i].get_width()) {
            return true;
        }
    }
    return false;
}

float PlatformManager::findPlatformY(float x) const {
    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (platforms[i].is_active() && x >= platforms[i].get_x() && x <= platforms[i].get_x() + platforms[i].get_width()) {
            return platforms[i].get_y();
        }
    }
    return -1;  // Return -1 if no platform is found at the x position
}
