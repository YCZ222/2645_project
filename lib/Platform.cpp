#include "Platform.h"

Platform::Platform() : _x(-1), _width(0), _y(0), _active(false) {
    
}

Platform::Platform(float x, float width, float y)
    : _x(x), _width(width), _y(y), _active(false) {}

void Platform::update(float dt) {
    if (_active) {
        _x -= dt * 0.5;  
    }
}

void Platform::draw(N5110 &lcd) {
    if (_active) {
        lcd.drawRect(_x, _y, _width, PLATFORM_HEIGHT, FILL_BLACK);  
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
