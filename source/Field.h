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
    void CreateCandSprite(class Game *game, bool turn);
    void DeleteCandSprite();

    // add/delete path
    void AddPath(class Path* path);
    void RemovePath(class Path* path);

    //getter
    std::vector<class Path*> GetPaths(){return mPaths;}
    
private:
    // edges form this field
    //std::vector<class Path> mPaths;
    class SpriteComponent *mTemporalCandSprite;
    std::vector<class Path*> mPaths;
};