#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include <vector>
#include <memory>

class Field : public Actor
{
public:
    Field(std::unique_ptr<class Game>& game, float x, float y);
    ~Field();
    // floating move ?
    void CreateCandSprite(std::unique_ptr<class Game>& game, bool turn);
    void DeleteCandSprite();

private:
    // edges form this field
    //std::vector<class Path> mPaths;
    class SpriteComponent *mTemporalCandSprite;
};