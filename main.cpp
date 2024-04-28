#include "mbed.h"
#include "N5110.h"
#include "Joystick.h"
#include "DigitalIn.h"
#include "GameEngine.h"

// Hardware setup
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_3, PC_2);
DigitalIn button(BUTTON1);
GameEngine game(joystick, button);

int main() {
    game.init(lcd);  // 初始化游戏引擎并传递LCD对象
    while (1) {
        game.update();  // 更新游戏逻辑，包括障碍物和玩家的状态
        game.draw(lcd);  // 绘制当前游戏状态到LCD
        ThisThread::sleep_for(30ms);  // 控制游戏更新的频率
    }
}