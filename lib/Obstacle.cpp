#include "Obstacle.h"

Obstacle::Obstacle() : _x(-1), _width(0), _height(0), _active(false) {
    // _x 设为 -1 表示初始时在屏幕外
}


Obstacle::Obstacle(float x, float width, float height)
    : _x(x), _width(width), _height(height), _active(false) {}

void Obstacle::update(float dt) {
    if (_active) {
        _x -= dt * 1;  // Assume some speed of movement
    }
}

void Obstacle::draw(N5110 &lcd) {
    if (_active) {
        lcd.drawRect(_x, 32 - _height, _width, _height, FILL_BLACK);
    }
}

void Obstacle::activate(float x, float width, float height) {
    _x = x;
    _width = width;
    _height = height;
    _active = true;
}

void Obstacle::deactivate() {
    _active = false;
}

float Obstacle::get_x() const {
    return _x;
}

float Obstacle::get_width() const {
    return _width;
}

bool Obstacle::is_active() const {
    return _active;
}

float Obstacle::get_height() const {
    return _height;
}

