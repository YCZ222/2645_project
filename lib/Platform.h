#ifndef PLATFORM_H
#define PLATFORM_H

#include "N5110.h"

class Platform {
public:
    Platform();
    Platform(float x, float width, float y);  
    void update(float dt);
    void draw(N5110 &lcd);
    void activate(float x, float width, float y);  
    void deactivate();

    float get_x() const;
    float get_width() const;
    float get_y() const;  
    bool is_active() const;

private:
    float _x, _width, _y;  
    static constexpr float PLATFORM_HEIGHT = 1.0f;  
    bool _active;
};

#endif
