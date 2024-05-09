#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include "Platform.h"
#include "N5110.h"

class PlatformManager {
public:
    PlatformManager();
    void update(float dt);
    void draw(N5110 &lcd);
    void generate();
    bool isOnPlatform(float x, float y, float velocity_y) const;  
    float findPlatformY(float x) const;  

private:
    static constexpr int MAX_PLATFORMS = 5;
    Platform platforms[MAX_PLATFORMS];
    int spawnCounter;
};

#endif

