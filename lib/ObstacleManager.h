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

private:
    static constexpr int MAX_OBSTACLES = 2;
    Obstacle obstacles[MAX_OBSTACLES];
    int spawnCounter;
    int last_x = 81; // Starting position for the first obstacle
};

#endif