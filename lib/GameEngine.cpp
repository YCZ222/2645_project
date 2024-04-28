#include "GameEngine.h"
#include <cstdlib>



// 使用数组来管理平台和障碍物，无需默认构造函数
Obstacle obstacles[MAX_OBSTACLES];
Platform platforms[MAX_PLATFORMS]; // 假设 Platform 类似 Obstacle
static int last_x = 81; // 初始平台位置
static int last_y = 40; // 初始平台高度
int y_variation = 16;
int x_distance = 10;  // Y轴最大变化设为5单位

GameEngine::GameEngine(Joystick &joystick, DigitalIn &button)
    : joystick(joystick), button(button), player_x(1), player_y(45), is_jumping(false), velocity_y(0), obstacle_spawn_counter(0), platform_spawn_counter(0) {
    // 现在数组初始化成员
    for (int i = 0; i < MAX_OBSTACLES; i++) {
    obstacles[i] = Obstacle(81, 5 + std::rand() % 5, 5 + std::rand() % 5);
    obstacles[i].deactivate(); // 初始时设为非激活状态
}

// 对于平台，实现类似的逻辑
    for (int i = 0; i < MAX_PLATFORMS; i++) {
    platforms[i] = Platform(81, 15, rand() % 45); // 使用假定的 Platform 构造函数参数
    platforms[i].deactivate(); // 初始时设为非激活状态
}

}




void GameEngine::init(N5110 &lcd) {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.5);
    lcd.setBrightness(0.55); 
    joystick.init();
     
}

void GameEngine::update() {
    
        // Player movement
    if (joystick.get_direction() == E) {
        player_x--;
    } else if (joystick.get_direction() == W) {
        player_x++;
    }

    // Player jumping
    if (!is_jumping && button.read() == 0) {
        is_jumping = true;
        velocity_y = JUMP_HEIGHT;
    }

    if (is_jumping) {
        player_y += velocity_y;
        velocity_y += GRAVITY;
        if (player_y >= 40) {
            player_y = 40;
            is_jumping = false;
        }
    }

    
   // Gravity logic
    if (!isOnPlatform(player_x, player_y)) {
    velocity_y += GRAVITY;
    player_y += velocity_y;

    // 如果玩家向下移动并且落在平台上，停止下落并调整位置
        if (velocity_y > 0 && isOnPlatform(player_x, player_y)) {
        velocity_y = 0;
        player_y = findPlatformY(player_x) - 2;  // 将玩家位置调整至平台顶部
        is_jumping = false;
    }
}
    else {
    // 如果玩家已经在平台上，则重置垂直速度并调整位置
    velocity_y = 0;
    player_y = findPlatformY(player_x) - 2;
    is_jumping = false;
}


    // Obstacle logic
    if (++obstacle_spawn_counter >= 20) {
        obstacle_spawn_counter = 0;
        generate_obstacle();
    }

    // Platform logic
    if (++platform_spawn_counter >= 20) {
        platform_spawn_counter = 0;
        generate_platform();
    }




    // Ensure player stays within bounds
    boundary(player_x, player_y);



    for (int i = 0; i < MAX_OBSTACLES; ++i) {
        obstacles[i].update(1.0);
        // 如果障碍物移出屏幕左侧，则重置其位置到屏幕右侧
        if (obstacles[i].get_x() < -obstacles[i].get_width()) {
            obstacles[i].activate(81, 5 + std::rand() % 5, 5 + std::rand() % 5);
        }
    }

    for (int i = 0; i < MAX_PLATFORMS; ++i) {
    platforms[i].update(1.0);
    if (platforms[i].get_x() < -platforms[i].get_width()) {  // 当平台离开屏幕
        int new_y = last_y + (rand() % (2 * y_variation + 1) - y_variation);
        new_y = std::max(std::min(new_y, 40), 10);  // 再次确保Y坐标在屏幕范围内
        platforms[i].activate(81 + x_distance, 15, new_y);
        last_x = 81 + x_distance;  // 更新last_x为屏幕宽度加上间距
        last_y = new_y;  // 更新last_y为重新激活的平台的 Y 坐标
    }
}



}



void GameEngine::draw(N5110 &lcd) {
    lcd.clear();
    lcd.drawRect(player_x, player_y, 2, 2, FILL_BLACK); // Draw player
    lcd.drawRect(0, 0, 84, 48, FILL_TRANSPARENT);

    // Draw each obstacle
    for (int i = 0; i < MAX_OBSTACLES; ++i) {
        if (obstacles[i].is_active() && obstacles[i].get_x() + obstacles[i].get_width() > 0) {
            int drawX = (obstacles[i].get_x() < 0) ? 0 : obstacles[i].get_x();
            int visibleWidth = (obstacles[i].get_x() < 0) ? obstacles[i].get_width() + obstacles[i].get_x() : obstacles[i].get_width();
            if (visibleWidth > 0) {
                lcd.drawRect(drawX, 32 - obstacles[i].get_height(), visibleWidth, obstacles[i].get_height(), FILL_BLACK);
            }
        }
    }

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

    lcd.refresh();
}






bool GameEngine::isOnPlatform(float x, float y) {
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


float GameEngine::findPlatformY(float x) {
    for (int i = 0; i < MAX_PLATFORMS; ++i) {
        if (platforms[i].is_active() && x >= platforms[i].get_x() && x <= platforms[i].get_x() + platforms[i].get_width()) {
            return platforms[i].get_y();
        }
    }
    return -1;
}




void GameEngine::generate_obstacle() {
    for (int i = 0; i < MAX_OBSTACLES; ++i) {
        if (!obstacles[i].is_active()) {
            obstacles[i].activate(81, 5 + std::rand() % 5, 5 + std::rand() % 5);
            break;
        }
    }
}

void GameEngine::generate_platform() {
      // X轴间距固定为40


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






void GameEngine::boundary(int x, int y){
    if (x < 1 ){        //ensure that the point doesnt pass beyond the left hand side of the screen
        player_x = 1;
    }else if (x > 81){  //ensure that the point doesnt pass beyond the right hand side of the screen-
        player_x = 81;
    }

    if(y < 1){          //ensure that the point doesnt pass beyond the top of the screen
        player_y = 1;
    }else if(y > 45){   //ensure that the point doesnt pass beyond the bottom of the screen
        player_y = 45;
    }
}