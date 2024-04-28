#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "N5110.h"

class Obstacle {
public:
    Obstacle();
    Obstacle(float x, float width, float height);
    void update(float dt);
    void draw(N5110 &lcd);
    void activate(float x, float width, float height);
    void deactivate();

    float get_x() const;
    float get_width() const;
    bool is_active() const;
    float get_height() const;

private:
    float _x, _width, _height;
    bool _active;
};

#endif
