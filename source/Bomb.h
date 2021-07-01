#pragma once
#include "Actor.h"

class Bomb : public Actor
{
public:
    Bomb(class Game* game, class TBPlayer* owner);
    ~Bomb();
private:
    class TBPlayer* mBombOwner;
};