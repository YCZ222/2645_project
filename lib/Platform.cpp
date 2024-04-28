#include "Platform.h"

Platform::Platform() : _x(-1), _width(0), _y(0), _active(false) {
    // _x 设为 -1 表示初始时在屏幕外
}




Platform::Platform(float x, float width, float y)
    : _x(x), _width(width), _y(y), _active(false) {}

void Platform::update(float dt) {
    if (_active) {
        _x -= dt * 0.6;  // 控制平台移动速度，这个值可以根据需要调整
    }
}

void Platform::draw(N5110 &lcd) {
    if (_active) {
        lcd.drawRect(_x, _y, _width, PLATFORM_HEIGHT, FILL_BLACK);  // 平台高度为常量 HEIGHT
    }
}

void Platform::activate(float x, float width, float y) {
    _x = x;
    _width = width;
    _y = y;
    _active = true;
}

void Platform::deactivate() {
    _active = false;
}

float Platform::get_x() const {
    return _x;
}

float Platform::get_width() const {
    return _width;
}

float Platform::get_y() const {
    return _y;
}

bool Platform::is_active() const {
    return _active;
}
