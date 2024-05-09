#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "N5110.h"

class Obstacle {
public:
    virtual ~Obstacle() {}
    virtual void update(float dt) = 0;
    virtual void draw(N5110 &lcd) = 0;
    virtual void activate(float x, float y, float width, float height) = 0;
    virtual void deactivate() = 0;
    virtual float get_x() const = 0;
    virtual float get_y() const = 0;
    virtual float get_width() const = 0;
    virtual float get_height() const = 0;
    virtual bool is_active() const = 0;
};

class SpaceJunk : public Obstacle {
private:
    float _x, _y, _width, _height;
    bool _active;
public:
    SpaceJunk();
    SpaceJunk(float x, float y, float width, float height);
    void update(float dt) override;
    void draw(N5110 &lcd) override;
    void activate(float x, float y, float width, float height) override;
    void deactivate() override;
    float get_x() const override;
    float get_y() const override;
    float get_width() const override;
    float get_height() const override;
    bool is_active() const override;
};

class Bullet : public Obstacle {
private:
    float _x, _y, _width, _height;
    bool _active;
public:
    Bullet();
    Bullet(float x, float y, float width, float height);
    void update(float dt) override;
    void draw(N5110 &lcd) override;
    void activate(float x, float y, float width, float height) override;
    void deactivate() override;
    float get_x() const override;
    float get_y() const override;
    float get_width() const override;
    float get_height() const override;
    bool is_active() const override;
};

#endif // OBSTACLE_H
