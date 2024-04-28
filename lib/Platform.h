#ifndef PLATFORM_H
#define PLATFORM_H

#include "N5110.h"

class Platform {
public:
    Platform();
    Platform(float x, float width, float y);  // 增加 y 坐标参数
    void update(float dt);
    void draw(N5110 &lcd);
    void activate(float x, float width, float y);  // 增加 y 坐标的激活参数
    void deactivate();

    float get_x() const;
    float get_width() const;
    float get_y() const;  // 返回 y 坐标
    bool is_active() const;

private:
    float _x, _width, _y;  // 增加 y 坐标
    static constexpr float PLATFORM_HEIGHT = 1.0f;  // 平台高度为1个像素
    bool _active;
};

#endif
