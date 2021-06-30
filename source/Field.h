#include "Actor.h"
#include "SpriteComponent.h"
#include <vector>

class Field : public Actor
{
public:
    Field(class Game* game);
    // floating move ?
    //void UpdateActor(float deltaTime)override;
    
private:
    // edges form this field
    //std::vector<class Path> mPaths;
};