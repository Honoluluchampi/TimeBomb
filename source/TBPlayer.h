#pragma once
#include "Actor.h"

class TBPlayer : public Actor
{
public:
    TBPlayer(class Game* game);
    ~TBPlayer(); // call the ending manager
};