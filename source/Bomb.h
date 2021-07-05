#pragma once
#include "Actor.h"

class Bomb : public Actor
{
public:
    Bomb(class Game* game, class TBPlayer* owner, class Field *field, int &count);
    ~Bomb();

    // change count function
    void SetCount(int &count){mCount = count;}
    void SetCountSprite();
    void ChangeCountSprite();
    void DecrementCount();
    void CheckBombCount();
private:
    int mCount;
    class TBPlayer* mBombOwner;
    class SpriteComponent* mCountSprite;
    class Field* mField;
};