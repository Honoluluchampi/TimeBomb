#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include <vector>

class Field : public Actor
{
public:
    Field(class Game* game, float x, float y);
    ~Field();
    // floating move ?
    //void UpdateActor(float deltaTime)override;
    
private:
    // edges form this field
    //std::vector<class Path> mPaths;
};