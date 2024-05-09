#include "Obstacle.h"

// SpaceJunk methods
SpaceJunk::SpaceJunk() : _x(0), _y(0), _width(0), _height(0), _active(false) {}

SpaceJunk::SpaceJunk(float x, float y, float width, float height)
    : _x(x), _y(y), _width(width), _height(height), _active(false) {}

void SpaceJunk::update(float dt) {
    if (_active) {
        _x -= dt * 0.4 ;  // Adjust speed for Space Junk
    }
}

void SpaceJunk::draw(N5110 &lcd) {
    if (_active) {
        lcd.drawRect(_x, _y, _width, _height, FILL_BLACK);
    }
}

void SpaceJunk::activate(float x, float y, float width, float height) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _active = true;
}

void SpaceJunk::deactivate() {
    _active = false;
}

float SpaceJunk::get_x() const { return _x; }
float SpaceJunk::get_y() const { return _y; }
float SpaceJunk::get_width() const { return _width; }
float SpaceJunk::get_height() const { return _height; }
bool SpaceJunk::is_active() const { return _active; }

// Bullet methods
Bullet::Bullet() : _x(0), _y(0), _width(0), _height(0), _active(false) {}

Bullet::Bullet(float x, float y, float width, float height)
    : _x(x), _y(y), _width(width), _height(height), _active(false) {}

void Bullet::update(float dt) {
    if (_active) {
        _x -= dt * 0.8;  // Adjust speed for bullets
    }
}

void Bullet::draw(N5110 &lcd) {
    if (_active) {
        lcd.drawRect(_x, _y, _width, _height, FILL_BLACK);
    }
}

void Bullet::activate(float x, float y, float width, float height) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _active = true;
}

void Bullet::deactivate() {
    _active = false;
}

float Bullet::get_x() const { return _x; }
float Bullet::get_y() const { return _y; }
float Bullet::get_width() const { return _width; }
float Bullet::get_height() const { return _height; }
bool Bullet::is_active() const { return _active; }
