#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H

#include "Obstacle.h"
#include "N5110.h"

class ObstacleManager {
public:
    ObstacleManager();
    void update(float dt);
    void draw(N5110 &lcd);
    void generate();
    static bool checkCollision(float x1, float y1, float width1, float height1,
                               float x2, float y2, float width2, float height2);
    bool checkPlayerCollision(float x, float y);

private:
    static const int MAX_OBSTACLES = 7;  
    SpaceJunk spaceJunks[2];
    Bullet bullets[5];
    int last_x = 81;
    int spawnCounter;
};

#endif
